// #################### Header Files ##############################

#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <bits/stdc++.h>
#include <mutex>
#include <atomic>

#include <chrono>
#include <cmath>
#include <memory>
#include <functional>
#include <string>
#include <typeinfo>

#include <config_parser/config_parser.h>
#include <sockets.hpp>
#include <motor.hpp>
#include <motor_controls.hpp>
#include <motor_interface.hpp>

//###### Motor #######
#include "socketcan/printd.c"
#include "socketcan/socketcan.c"
#include "canopen/canopen.h"
#include "canopen/NMT.c"
#include "canopen/PDO.c"
#include "canopen/SDO.c"

// ### Spd logger ###
#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
// ##################

// ############################ Robot Hardware config ##########################

// ConfigParser::ConfigParserSPtr config_parser = std::make_shared<ConfigParser>();
// Sockets::SocketsSPtr left_motor_sockets = std::make_shared<Sockets>();
// Motor::MotorSPtr motor_sockets = std::make_shared<Motor>();
MotorControls::MotorControlsSPtr motor_controls_ ;
// ############################ Namespace ##########################

std::shared_ptr<spdlog::logger>  logger_motors;

int main(int argc, char * argv[]){

    rclcpp::init(argc, argv);
    std::cout << "in interface initialization.." << std::endl;
    std::shared_ptr<MotorInterface> node;
    node = std::make_shared<MotorInterface>();
    rclcpp::executors::MultiThreadedExecutor executor;
    executor.add_node(node);

    MotorControls::position_cmd_t position_cmd_element_;
    MotorControls::velocity_cmd_t velocity_cmd_element_;
    position_cmd_element_ = {.timeout =10,
    .relative_pos=0,
    .max_vel=0,
    .accel=0,
    .decel=0
    };

    velocity_cmd_element_ = {.timeout =10,
    .velocity=1,
    .max_vel=20,
    .accel=1,
    .decel=1
    };
    //std::cout << "sending velocity" << std::endl;
    //motor_controls_->motor_command(0x0C, "velocity", position_cmd_element_, velocity_cmd_element_);

    while(rclcpp::ok()) {
        executor.spin_some();
	    //logger->debug("spin some");
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    rclcpp::shutdown();
    return 0;
}
