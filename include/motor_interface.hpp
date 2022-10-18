#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

#include <motor_params.hpp>
#include <motor.hpp>
#include <motor_controls.hpp>
#include <rclcpp/rclcpp.hpp>

using std::placeholders::_1;

class MotorInterface: public rclcpp::Node {
    private:

    public:

    MotorInterface();
    ~MotorInterface();

    std::shared_ptr<MotorInterface> MotorInterfaceSPtr;
    std::unique_ptr<MotorInterface> MotorInterfaceUPtr;

    // Read loop
    rclcpp::TimerBase::SharedPtr timer_;
    void readMotorData();
  
};

#endif 
