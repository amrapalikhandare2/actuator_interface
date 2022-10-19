#include <motor_interface.hpp>


MotorInterface::MotorInterface() : Node("motor_interface"){

    timer_ = this->create_wall_timer(std::chrono::seconds(10), std::bind(&MotorInterface::readMotorData, this));
    
    left_front_motor_sockets_ = std::make_shared<Sockets>(0x0C);
    right_front_motor_sockets_ = std::make_shared<Sockets>(0x0D);
    //left_rear_motor_sockets_ = std::make_shared<Sockets>(0x0E);
    //right_rear_motor_sockets_ = std::make_shared<Sockets>(0x0F);

    left_front_motor_ = std::make_shared<Motor>(left_front_motor_sockets_);
    right_front_motor_ = std::make_shared<Motor>(right_front_motor_sockets_);
    //left_rear_motor_ = std::make_shared<Motor>(left_rear_motor_sockets_ );
    //right_rear_motor_ = std::make_shared<Motor>(right_rear_motor_sockets_);

    left_front_motor_controls_  = std::make_shared<MotorControls>(left_front_motor_sockets_);
    right_front_motor_controls_  = std::make_shared<MotorControls>(right_front_motor_sockets_);
    //left_rear_motor_controls_  = std::make_shared<MotorControls>(left_rear_motor_sockets_);
    //right_rear_motor_controls_  = std::make_shared<MotorControls>(right_rear_motor_sockets_);
    std::cout <<"sleep" << std::endl;
    sleep(2);
    left_front_motor_->motor_init(0x0C);
    std::cout <<"sleep" << std::endl;
    sleep(2);
    right_front_motor_->motor_init(0x0D);
    std::cout <<"sleep" << std::endl;
    sleep(2);
    //left_rear_motor_->motor_init(0x0E);
    //std::cout <<"sleep" << std::endl;
    //sleep(2);
    //right_rear_motor_->motor_init(0x0F);
    //std::cout <<"sleep" << std::endl;
    //sleep(2);

    left_front_motor_->motor_enable(0x0C);
    std::cout <<"sleep" << std::endl;
    sleep(2);
    right_front_motor_->motor_enable(0x0D);
    std::cout <<"sleep" << std::endl;
    sleep(2);
    //left_rear_motor_->motor_enable(0x0E);
    //sleep(2);
    //right_rear_motor_->motor_enable(0x0F);
    //sleep(2);
    
    MotorControls::position_cmd_t position_cmd_element_;
    MotorControls::velocity_cmd_t velocity_cmd_element_;
    
    position_cmd_element_ = {.timeout =10,
    .relative_pos=0,
    .max_vel=0,
    .accel=0,
    .decel=0
    };

    velocity_cmd_element_ = {.timeout =10,
    .velocity=15,
    .max_vel=20,
    .accel=1,
    .decel=1
    };
    std::cout << "sending velocity" << std::endl;
    left_front_motor_controls_->motor_command(0x0C, "velocity", position_cmd_element_, velocity_cmd_element_);
    right_front_motor_controls_->motor_command(0x0D, "velocity", position_cmd_element_, velocity_cmd_element_);

}

MotorInterface::~MotorInterface(){

}

void MotorInterface::readMotorData(){

}
