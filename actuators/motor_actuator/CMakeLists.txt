cmake_minimum_required(VERSION 3.8)
project(motor_actuator)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

include_directories(
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../json_reader/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../motor/include
)

install(DIRECTORY include/
        DESTINATION include/
        )


# set(socket_SRCS
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../socketcan/socketcan.c
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../socketcan/socketcan.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../socketcan/printd.c
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../socketcan/printd.h
# )

# set(canopen_SRCS
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../canopen/canopen.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../canopen/NMT.c
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../canopen/NMT.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../canopen/PDO.c
#         ${CMAKE_CURRENT_SOURCE_DIR}/ ../../canopen/PDO.h
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../canopen/SDO.c
#         ${CMAKE_CURRENT_SOURCE_DIR}/../../canopen/SDO.h
# )


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(actuator REQUIRED)
find_package(motor REQUIRED)

add_library(${PROJECT_NAME} SHARED
        src/motor_actuator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../json_reader/src/json_read.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../motor/src/sockets.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../motor/src/motor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../motor/src/motor_controls.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../motor/src/motor_feedback.cpp
        
        )

# add_library(socketcan SHARED ${socket_SRCS})
# add_library(canopen SHARED ${canopen_SRCS})
# target_link_libraries(${PROJECT_NAME} canopen socketcan)

target_link_libraries(${PROJECT_NAME}
        pthread
        jsoncpp
        )

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_target_dependencies(${PROJECT_NAME}
        actuator
        motor
        )

install(
        TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include

)

add_executable(${PROJECT_NAME}_test
        test/main.cpp)

target_link_libraries(${PROJECT_NAME}_test

        ${PROJECT_NAME}
        pthread
        jsoncpp
        )

ament_target_dependencies(${PROJECT_NAME}_test
        actuator
        motor
        )

install(
        TARGETS ${PROJECT_NAME}_test
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib/${PROJECT_NAME}
        RUNTIME DESTINATION lib/${PROJECT_NAME}
        DESTINATION lib/${PROJECT_NAME}

)


if (BUILD_TESTING)
    find_package(ament_lint_auto REQUIRED)
    set(ament_cmake_copyright_FOUND TRUE)
    set(ament_cmake_cpplint_FOUND TRUE)
    ament_lint_auto_find_test_dependencies()
endif ()

ament_package()