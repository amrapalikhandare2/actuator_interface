cmake_minimum_required(VERSION 3.5)
project(actuator_interface)

## Sources
set(socket_SRCS
    socketcan/socketcan.c
    socketcan/socketcan.h
    socketcan/printd.c
    socketcan/printd.h
)

set(canopen_SRCS
    canopen/canopen.h
    canopen/NMT.c
    canopen/NMT.h
    canopen/PDO.c
    canopen/PDO.h
    canopen/SDO.c
    canopen/SDO.h
)


if(UNIX)
    list(APPEND serial_SRCS RightbotDrivers/serial/impl/unix.cc)
    list(APPEND serial_SRCS RightbotDrivers/serial/impl/list_ports/list_ports_linux.cc)
endif()

if(NOT TARGET spdlog)
    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()


## Add serial library

include_directories(${CMAKE_CURRENT_SOURCE_DIR})



# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -fPIC -Wextra -Wpedantic)
endif()
	
find_package(ament_cmake REQUIRED)
find_package(jsoncpp REQUIRED) 
find_package(rclcpp REQUIRED)

include_directories(
    include
    json_reader/include
    config_parser/include
)

add_library(socketcan SHARED ${socket_SRCS})
add_library(canopen SHARED ${canopen_SRCS})
target_link_libraries(canopen socketcan)


add_library(${PROJECT_NAME} SHARED
            src/sockets.cpp
            src/motor.cpp
            src/motor_controls.cpp
            src/motor_feedback.cpp
            src/motor_interface.cpp
            test/test_actuator_interface.cpp
            )
target_link_libraries(${PROJECT_NAME} canopen socketcan)
ament_target_dependencies(${PROJECT_NAME} rclcpp)

add_executable(test_actuator_interface config_parser/src/config_parser.cpp test/test_actuator_interface.cpp)
add_dependencies(test_actuator_interface ${PROJECT_NAME})
target_link_libraries(test_actuator_interface ${PROJECT_NAME} spdlog::spdlog jsoncpp)


install(TARGETS	
  test_actuator_interface
  ${PROJECT_NAME}	
  DESTINATION lib/${PROJECT_NAME}		
)

#install(DIRECTORY launch
#  DESTINATION share/${PROJECT_NAME}
#)
ament_package()

