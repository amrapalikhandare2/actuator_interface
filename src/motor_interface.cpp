#include <motor_interface.hpp>


MotorInterface::MotorInterface() : Node("motor_interface"){

    timer_ = this->create_wall_timer(std::chrono::seconds(10), std::bind(&MotorInterface::readMotorData, this));

    Motor::MotorSPtr left_front_motor_ = std::make_shared<Motor>();
    Motor::MotorSPtr right_front_motor_ = std::make_shared<Motor>();
    Motor::MotorSPtr left_rear_motor_ = std::make_shared<Motor>();
    Motor::MotorSPtr right_rear_motor_ = std::make_shared<Motor>();

    MotorControls::MotorControlsSPtr left_front_motor_controls_  = std::make_shared<MotorControls>();
    MotorControls::MotorControlsSPtr right_front_motor_controls_  = std::make_shared<MotorControls>();
    MotorControls::MotorControlsSPtr left_rear_motor_controls_  = std::make_shared<MotorControls>();
    MotorControls::MotorControlsSPtr right_rear_motor_controls_  = std::make_shared<MotorControls>();

    left_front_motor_->motor_init(0x0C);
    right_front_motor_->motor_init(0x0D);
    left_rear_motor_->motor_init(0x0E);
    right_rear_motor_->motor_init(0x0F);

    left_front_motor_->motor_enable(0x0C);
    right_front_motor_->motor_enable(0x0D);
    left_rear_motor_->motor_enable(0x0E);
    right_rear_motor_->motor_enable(0x0F);


    
}

MotorInterface::~MotorInterface(){

}

void MotorInterface::readMotorData(){

}