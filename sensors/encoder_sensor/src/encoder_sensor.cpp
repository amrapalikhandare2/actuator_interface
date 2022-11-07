#include <encoder_sensor/encoder_sensor.hpp>
using namespace std;


EncoderSensor::EncoderSensor(Sockets::SocketsSPtr motor_sockets){
    
    init_json();
    update_data_thread_ = std::thread(&EncoderSensor::updateData,this);
    motor_feedback_ = std::make_shared<MotorFeedback>(motor_sockets);
}

EncoderSensor::~EncoderSensor() {
    
    update_data_thread_.join();
}

void EncoderSensor::init_json(){

    JsonRead parser("/application/rightbot_ws/src/actuator_interface/sensors/encoder_sensor/config/config.json");

    if(!parser.parse())
        throw std::invalid_argument("Parsing error in Dummy Sensor 1s");

    parser.getValue(sensor_data_);

    motor_id_ = sensor_data_["motor_id"].asInt64();
}
void EncoderSensor::readData(int motor_id, EncoderData *encoder_data){

    motor_feedback_->motorFeedback(motor_id, &feedback_s_m_);
    encoder_data->status_m = feedback_s_m_.status_m;
    encoder_data->battery_vol_m = feedback_s_m_.battery_vol_m;
    encoder_data->pos_m = feedback_s_m_.pos_m;
    encoder_data->vel_m = feedback_s_m_.vel_m;
    encoder_data->manufacturer_reg_m = feedback_s_m_.manufacturer_reg_m;
    encoder_data->latched_fault_m = feedback_s_m_.latched_fault_m;
    
};

void EncoderSensor::updateData(){

    
    while(true){
    
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        read_mutex_.lock();

        readData(motor_id_, &encoder_data_);

        // sensor_data_["counts"]= sensor_data_["counts"].asInt() + 1;
        // sensor_data_["state"] = "running";

        // std::cout<< "Data Updated Sensor 1" <<std::endl;



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
