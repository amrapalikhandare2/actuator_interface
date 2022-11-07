#include <encoder_sensor/encoder_sensor.hpp>
using namespace std;


EncoderSensor::EncoderSensor(Sockets::SocketsSPtr motor_sockets){
    
    init_json();
    update_data_thread_ = std::thread(&EncoderSensor::updateData,this);
}

EncoderSensor::~EncoderSensor() {
    
    update_data_thread_.join();
}

void EncoderSensor::init_json(){

    JsonRead parser("/application/rightbot_ws/src/actuator_interface/sensors/encoder_sensor/config/config.json");

    if(!parser.parse())
        throw std::invalid_argument("Parsing error in Dummy Sensor 1s");

    parser.getValue(sensor_data_);
}

void EncoderSensor::updateData(){

    while(true){
    
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        read_mutex_.lock();

        sensor_data_["counts"]= sensor_data_["counts"].asInt() + 1;
        sensor_data_["state"] = "running";

        std::cout<< "Data Updated Sensor 1" <<std::endl;

        read_mutex_.unlock();
    }

}

void EncoderSensor::getData(Json::Value &sensor_data){
    
    read_mutex_.lock();

    sensor_data["counts"] = sensor_data_["counts"];
    sensor_data["state"] = sensor_data_["state"];
    
    std::cout<< "Data Read Sensor 1" <<std::endl;
    
    read_mutex_.unlock();
}
