#include <motor_interface.hpp>


MotorInterface::MotorInterface() : Node("motor_interface"){

    logger_ = spdlog::get("actuator_interface")->clone("motor_interface");

    read_timer_ = this->create_wall_timer(std::chrono::milliseconds(20), std::bind(&MotorInterface::readMotorData, this));
    data_request_timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&MotorInterface::requestMotorData, this));
    
    left_front_motor_sockets_ = std::make_shared<Sockets>(0x0C);
    right_front_motor_sockets_ = std::make_shared<Sockets>(0x0D);

    left_front_motor_ = std::make_shared<Motor>(left_front_motor_sockets_);
    right_front_motor_ = std::make_shared<Motor>(right_front_motor_sockets_);
    
    logger_->info("[Left Motor] Sockets ptr: {}", left_front_motor_sockets_);
    logger_->info("[Right Motor] Sockets ptr: {}", right_front_motor_sockets_);
    
    left_front_motor_->nmtChangeState("nmt_enter_preoperational");
    
    logger_->info("[Left Motor] Sending Initialization Command");
    left_front_motor_->motor_init(0x0C);
    logger_->info("[Left Motor] Initialization sleep time");
    sleep(2);
    logger_->info("[Right Motor] Sending Initialization Command");
    right_front_motor_->motor_init(0x0D);
    logger_->info("[Right Motor] Initialization sleep time");
    sleep(2);

    left_front_motor_->motor_enable(0x0C);
    logger_->info("[Left Motor] Initialization enable time");
    sleep(2);
    right_front_motor_->motor_enable(0x0D);
    logger_->info("[Right Motor] Initialization enable time");
    sleep(2);
    
    left_front_motor_->nmtChangeState("nmt_start_node");

    initialization_done = true;

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
    .max_vel=10,
    .accel=1,
    .decel=1
    };
    
    logger_->debug("[Left Motor] Sending Velocity");

    left_front_motor_->motorCommand(0x0C, "velocity", position_cmd_element_, velocity_cmd_element_);
    
    logger_->debug("[Right Motor] Sending Velocity");
    right_front_motor_->motorCommand(0x0D, "velocity", position_cmd_element_, velocity_cmd_element_);

}

MotorInterface::~MotorInterface(){

}

void MotorInterface::requestMotorData(){
    if (initialization_done){
	
	//logger_->info("Motor Data Request");
        //left_front_motor_->motor_request();
    }


}

void MotorInterface::readMotorData(){
    if (initialization_done){
        //logger_->info("Motor Data Read");
        left_front_motor_->motorFeedback(0x0C, &feedback_s_l_m_);
        //std::cout << "Motor Status: " << feedback_s_l_m_.status_m<< std::endl;
        //std::cout << "Battery Voltage: " << feedback_s_l_m_.battery_vol_m<< std::endl;
        //std::cout << "Motor Position: " << feedback_s_l_m_.pos_m<< std::endl;
        //std::cout << "Motor Velocity: " << feedback_s_l_m_.vel_m<< std::endl;
        //std::cout << "Motor Manufactuer Register: " << feedback_s_l_m_.manufacturer_reg_m<< std::endl;
        //std::cout << "Motor Latched Fault: " << feedback_s_l_m_.latched_fault_m<< std::endl;
        }
    

    

}
