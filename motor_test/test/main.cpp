#include <motor_test/motor_test.hpp>
#include <sockets.hpp>
#include <thread>
#include <condition_variable>
#include <chrono>

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"

using namespace std;

std::condition_variable cv;

// This mutex is used for three purposes:
// 1) to synchronize accesses to i
// 2) to synchronize accesses to std::cerr
// 3) for the condition variable cv
std::mutex cv_m;

bool message_received = false;

MotorTest::MotorTestSPtr motor_test;
Sockets::SocketsSPtr motor_sockets_1;
MotorActuator::MotorActuatorSPtr motor_actuator_1;
EncoderSensor::EncoderSensorSPtr motor_encoder_sensor_1;

Sockets::SocketsSPtr motor_sockets_2;
MotorActuator::MotorActuatorSPtr motor_actuator_2;
EncoderSensor::EncoderSensorSPtr motor_encoder_sensor_2;

Json::Value actuator_data;
std::mutex sync_mutex; // for sync of message_received variable

Json::Value sensor_data;

Json::Value sensor_data_1;

int main() {

    // motor_test = std::make_shared<MotorTest>();
    // motor_actuator_1 = std::make_shared<MotorActuator>(12, motor_sockets_1);
    // motor_sockets_1 = std::make_shared<Sockets>(12);
    spdlog::init_thread_pool(8192, 1);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt >();
    console_sink->set_level(spdlog::level::info);
    auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("/data/logs/robot_logs/actuator_interface_logs/motor_interface_logs.txt", 1024*1024*100, 3);
    rotating_sink->set_level(spdlog::level::debug);
    std::vector<spdlog::sink_ptr> sinks {console_sink,rotating_sink};
    auto root_logger = std::make_shared<spdlog::async_logger>("actuator_interface", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    root_logger->set_level(spdlog::level::debug);
    spdlog::register_logger(root_logger);

    motor_sockets_1 = std::make_shared<Sockets>(12);
    motor_sockets_2 = std::make_shared<Sockets>(13);

    motor_actuator_1 = std::make_shared<MotorActuator>(12,motor_sockets_1);
    motor_actuator_2 = std::make_shared<MotorActuator>(13,motor_sockets_2);

    motor_encoder_sensor_1 = std::make_shared<EncoderSensor>(12,motor_sockets_1);
    motor_encoder_sensor_2 = std::make_shared<EncoderSensor>(13,motor_sockets_2);

    motor_actuator_1->motorCommand(12, "velocity", motor_actuator_1->setPosition(0,0,0,0,0), motor_actuator_1->setVelocity(1,15,10,1,1) );
    // motor_actuator_2->motorCommand(13, "velocity", motor_actuator_2->setPosition(0,0,0,0,0), motor_actuator_2->setVelocity(1,15,10,1,1) );
    JsonRead parser("/application/rightbot_ws/src/actuator_interface/sensors/encoder_sensor/config/motor_data.json");

    if(!parser.parse())
        throw std::invalid_argument("test: Parsing error in Dummy Sensor 1s");

    parser.getValue(sensor_data);
   
    while(true){
	    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    	    motor_encoder_sensor_1->getData(sensor_data_1);
    
            std::cout << "test: status: " << sensor_data_1["status"].asInt64() << std::endl;
            std::cout << "test: battery voltage: " << sensor_data_1["battery_voltage"].asInt64() << std::endl;
            std::cout << "test: counts: " << sensor_data_1["counts"].asInt64() << std::endl;
            std::cout << "test: velocity: " << sensor_data_1["velocity"].asInt64() << std::endl;

    }

    return 0;

}
