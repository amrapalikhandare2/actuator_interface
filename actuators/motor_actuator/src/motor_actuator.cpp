#include <motor_actuator/motor_actuator.hpp>

using namespace std;


MotorActuator::MotorActuator() {
    init_json();
}

MotorActuator::~MotorActuator() = default;

void MotorActuator::init_json() {

    JsonRead parser(
            "/home/dhruv/Desktop/Rightbot_ros2_rolling_ws/hardware_interface_ws/src/dummy_actuators/dummy_actuator_1/config/config.json");

    if (!parser.parse())
        throw std::invalid_argument("Parsing error in Dummy actuator 1s");

    parser.getValue(actuator_data_);
}


void MotorActuator::writeData(Json::Value &actuator_data) {

    actuator_data_["counts"] = actuator_data["counts"];
    actuator_data_["state"] = actuator_data["state"];

    std::cerr << "Data Written actuator 1" << std::endl;
    std::cerr << "counts: " << actuator_data_["counts"] << std::endl;


}
