cmake_minimum_required(VERSION 3.8)
project(motor_test)

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

include_directories(
        include
        ${CMAKE_CURRENT_SOURCE_DIR}/../json_reader/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../motor/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../actuators/motor_actuator/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../sensors/encoder_sensor/include

)

install(DIRECTORY include/
        DESTINATION include/
        )


# find dependencies
find_package(ament_cmake REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(actuator REQUIRED)
find_package(motor_actuator REQUIRED)
find_package(motor REQUIRED)
find_package(sensor REQUIRED)
find_package(encoder_sensor REQUIRED)

add_library(${PROJECT_NAME} SHARED
        src/motor_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../motor/src/sockets.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/../m/src/motor_actuator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../json_reader/src/json_read.cpp
        )

target_link_libraries(${PROJECT_NAME}
        pthread
        jsoncpp
        )

ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_target_dependencies(${PROJECT_NAME}
        motor_actuator
        motor
        encoder_sensor
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
        # ${CMAKE_CURRENT_SOURCE_DIR}/../motor/src/sockets.cpp
        test/main.cpp)

target_link_libraries(${PROJECT_NAME}_test

        ${PROJECT_NAME}
        pthread
        jsoncpp
        )

ament_target_dependencies(${PROJECT_NAME}_test
        motor_actuator
        motor
        encoder_sensor
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