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
#include <gls_barcode.hpp>

//###### Motor #######
#include "../socketcan/printd.c"
#include "../socketcan/socketcan.c"
#include "../canopen/canopen.h"
#include "../canopen/NMT.c"
#include "../canopen/PDO.c"
#include "../canopen/SDO.c"

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

// ############################ Namespace ##########################

std::shared_ptr<spdlog::logger>  logger_;

int main(){

    
}
