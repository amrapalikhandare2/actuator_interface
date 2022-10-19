#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#include <motor_params.hpp>
#include <motor.hpp>
#include <motor_controls.hpp>
#include <rclcpp/rclcpp.hpp>
#include <iostream>
using std::placeholders::_1;

class MotorInterface: public rclcpp::Node {
    private:

    public:

    MotorInterface();
    ~MotorInterface();

    std::shared_ptr<MotorInterface> MotorInterfaceSPtr;
    std::unique_ptr<MotorInterface> MotorInterfaceUPtr;

    Sockets::SocketsSPtr left_front_motor_sockets_ ;
    Sockets::SocketsSPtr right_front_motor_sockets_ ;
    Sockets::SocketsSPtr left_rear_motor_sockets_ ;
    Sockets::SocketsSPtr right_rear_motor_sockets_ ;

    Motor::MotorSPtr left_front_motor_ ;
    Motor::MotorSPtr right_front_motor_ ;
    Motor::MotorSPtr left_rear_motor_ ;
    Motor::MotorSPtr right_rear_motor_ ;

    MotorControls::MotorControlsSPtr left_front_motor_controls_ ;
    MotorControls::MotorControlsSPtr right_front_motor_controls_ ;
    MotorControls::MotorControlsSPtr left_rear_motor_controls_ ;
    MotorControls::MotorControlsSPtr right_rear_motor_controls_ ;


    // Read loop
    rclcpp::TimerBase::SharedPtr timer_;
    void readMotorData();
  
};

#endif 
