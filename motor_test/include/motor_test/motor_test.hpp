#ifndef MOTOR_TEST_H_
#define MOTOR_TEST_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <json_reader/json_read.h>
#include <actuator/actuator.hpp>
#include <sockets.hpp>
#include <motor_actuator/motor_actuator.hpp>
#include <encoder_sensor/encoder_sensor.hpp>


class MotorTest{

public:

    typedef std::shared_ptr<MotorTest> MotorTestSPtr;
    typedef std::unique_ptr<MotorTest> MotorTestUPtr;

    MotorTest();

    ~MotorTest();


private:
    std::shared_ptr<spdlog::logger> logger_;

    Json::Value actuator_data_;
    // Sockets::SocketsSPtr motor_sockets_1;
    // MotorActuator::MotorActuatorSPtr motor_actuator_1 ;
    // EncoderSensor::EncoderSensorSPtr motor_encoder_sensor_1;
    
    int motor_id_;
    
};

#endif // MOTOR_TEST_H_