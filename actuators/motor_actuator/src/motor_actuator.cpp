#include <motor_actuator/motor_actuator.hpp>

using namespace std;


MotorActuator::MotorActuator(int motor_id, Sockets::SocketsSPtr motor_sockets) {
    // init_json();

    // motor initializations
    
    motor_ = std::make_shared<Motor>(motor_sockets);
    
    motor_controls_ = std::make_shared<MotorControls>(motor_sockets);
    motor_id_ = motor_id;

    motor_->motor_init(motor_id_);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    motor_->motor_enable(motor_id_);
    std::this_thread::sleep_for(std::chrono::seconds(2));

}

MotorActuator::~MotorActuator() = default;

void MotorActuator::init_json() {

    JsonRead parser(
            "/application/rightbot_ws/src/actuator_interface/actuators/motor_actuator/config/write_data.json");

    if (!parser.parse())
        throw std::invalid_argument("Parsing error in motor actuator");

    parser.getValue(actuator_data_);
}

bool MotorActuator::motorCommand(int motor_id, std::string command_type, MotorControls::position_cmd_t position_cmd_element, MotorControls::velocity_cmd_t velocity_cmd_element){
	motor_controls_->motor_command(motor_id, command_type, position_cmd_element, velocity_cmd_element);
}

MotorControls::position_cmd_t MotorActuator::setPosition(double timeout, double relative_pos, double max_vel, double accel, double decel){
    MotorControls::position_cmd_t position_cmd_element_;
    position_cmd_element_.timeout = timeout;
    position_cmd_element_.relative_pos = relative_pos;
    position_cmd_element_.max_vel = max_vel;
    position_cmd_element_.accel = accel;
    position_cmd_element_.decel = decel;
    
    return position_cmd_element_;
}

MotorControls::velocity_cmd_t MotorActuator::setVelocity(double timeout, double velocity, double max_vel, double accel, double decel){
    MotorControls::velocity_cmd_t velocity_cmd_element_ ;
    velocity_cmd_element_.timeout = timeout;
    velocity_cmd_element_.velocity = velocity;
    velocity_cmd_element_.max_vel = max_vel;
    velocity_cmd_element_.accel = accel;
    velocity_cmd_element_.decel = decel;
    
    return velocity_cmd_element_;
}

void MotorActuator::writeData(Json::Value &actuator_data) {

    actuator_data_["timeout"] = actuator_data["timeout"];
    actuator_data_["mode"] = actuator_data["mode"];
    actuator_data_["velocity"] = actuator_data["velocity"];
    actuator_data_["relative_pos"] = actuator_data["relative_pos"];
    actuator_data_["max_vel"] = actuator_data["max_vel"];
    actuator_data_["accel"] = actuator_data["accel"];
    actuator_data_["decel"] = actuator_data["decel"];

    if (actuator_data_["mode"].asString() == "velocity"){
        position_cmd_received_ = {0};
        velocity_cmd_received_.timeout = actuator_data_["timeout"].asDouble();
        velocity_cmd_received_.velocity = actuator_data_["velocity"].asDouble();
        velocity_cmd_received_.max_vel = actuator_data_["max_vel"].asDouble();
        velocity_cmd_received_.accel = actuator_data_["accel"].asDouble();
        velocity_cmd_received_.decel = actuator_data_["decel"].asDouble();
        motor_controls_->motor_command(motor_id_, "velocity", position_cmd_received_, velocity_cmd_received_);

    }

    if (actuator_data_["mode"].asString()== "position"){
        velocity_cmd_received_ = {0};
        position_cmd_received_.timeout = actuator_data_["timeout"].asDouble();
        position_cmd_received_.relative_pos = actuator_data_["relative_pos"].asDouble();
        position_cmd_received_.max_vel = actuator_data_["max_vel"].asDouble();
        position_cmd_received_.accel = actuator_data_["accel"].asDouble();
        position_cmd_received_.decel = actuator_data_["decel"].asDouble();
        motor_controls_->motor_command(motor_id_, "position", position_cmd_received_, velocity_cmd_received_);
        
    }



    // actuator_data_["counts"] = actuator_data["counts"];
    // actuator_data_["state"] = actuator_data["state"];

    // std::cerr << "Data Written actuator 1" << std::endl;
    // std::cerr << "counts: " << actuator_data_["counts"] << std::endl;


}
