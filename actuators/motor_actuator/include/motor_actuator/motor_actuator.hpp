#ifndef MOTOR_ACTUATOR_H_
#define MOTOR_ACTUATOR_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <json_reader/json_read.h>
#include <actuator/actuator.hpp>
#include <sockets.hpp>
#include <motor.hpp>
#include <motor_controls.hpp>

#include "../../socketcan/printd.c"
#include "../../socketcan/socketcan.c"
#include "../../canopen/canopen.h"
#include "../../canopen/NMT.c"
#include "../../canopen/PDO.c"
#include "../../canopen/SDO.c"

class MotorActuator : public Actuator {

public:

    typedef std::shared_ptr<MotorActuator> MotorActuatorSPtr;
    typedef std::unique_ptr<MotorActuator> MotorActuatorUPtr;

    MotorActuator(int motor_id, Sockets::SocketsSPtr motor_sockets);

    ~MotorActuator();

    void writeData(Json::Value &actuator_data) override;
    MotorControls::position_cmd_t setPosition(double timeout, double relative_pos, double max_vel, double accel, double decel);
    MotorControls::velocity_cmd_t setVelocity(double timeout, double velocity, double max_vel, double accel, double decel);
    bool motorCommand(int motor_id, std::string command_type, MotorControls::position_cmd_t position_cmd_element, MotorControls::velocity_cmd_t velocity_cmd_element);
    
private:

    Json::Value actuator_data_;
    Sockets::SocketsSPtr motor_sockets_;
    Motor::MotorSPtr motor_ ;
    MotorControls::MotorControlsSPtr motor_controls_;
    std::shared_ptr<spdlog::logger> logger_;
    // bool motorCommand(int motor_id, std::string command_type, MotorControls::position_cmd_t position_cmd_element, MotorControls::velocity_cmd_t velocity_cmd_element);
    int motor_id_;
    void init_json();
    

};

#endif // MOTOR_ACTUATOR_H_