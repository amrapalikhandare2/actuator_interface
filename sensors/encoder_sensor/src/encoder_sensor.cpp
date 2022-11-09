#include <encoder_sensor/encoder_sensor.hpp>
using namespace std;

EncoderSensor::EncoderSensor(int motor_id, Sockets::SocketsSPtr motor_sockets){
    
    // init_json();
    logger_ = spdlog::get("actuator_interface")->clone("encoder_sensor");
    read_motor_data_thread_ = std::thread(&EncoderSensor::readMotorData,this);
    motor_feedback_ = std::make_shared<MotorFeedback>(motor_sockets);
    motor_id_ = motor_id;
    read_err_ = 0;
    update_data_thread_ = std::thread(&EncoderSensor::updateData, this);
    message_received = false;
}

EncoderSensor::~EncoderSensor() {
    
    read_motor_data_thread_.join();
    update_data_thread_.join();
    
}

void EncoderSensor::init_json(){

    JsonRead parser("/application/rightbot_ws/src/actuator_interface/sensors/encoder_sensor/config/config.json");

    if(!parser.parse())
        throw std::invalid_argument("Parsing error in Dummy Sensor 1s");

    parser.getValue(sensor_data_);

    // motor_id_ = sensor_data_["motor_id"].asInt64();
}
void EncoderSensor::readData(int motor_id, EncoderData *encoder_data){

    read_err_ =  motor_feedback_->motorFeedback(motor_id, &feedback_s_m_);
    encoder_data->status_m = feedback_s_m_.status_m;
    encoder_data->battery_vol_m = feedback_s_m_.battery_vol_m;
    encoder_data->pos_m = feedback_s_m_.pos_m;
    encoder_data->vel_m = feedback_s_m_.vel_m;
    encoder_data->manufacturer_reg_m = feedback_s_m_.manufacturer_reg_m;
    encoder_data->latched_fault_m = feedback_s_m_.latched_fault_m;

    logger_->info("Motor Sensor: {}",encoder_data->status_m );
    logger_->info("Motor Battery: {}",encoder_data->battery_vol_m );
    logger_->info("Motor Position: {}",encoder_data->pos_m );
    logger_->info("Motor Velocity: {}",encoder_data->vel_m );
    logger_->info("Motor Manufacturer Reg: {}",encoder_data->manufacturer_reg_m );
    logger_->info("Motor Latched Fault: {}",encoder_data->latched_fault_m );

    // std::cout << "Motor Sensor: " << encoder_data->status_m << std::endl; 
    // std::cout << "Motor Battery: " << encoder_data->battery_vol_m << std::endl; 
    // std::cout << "Motor Position: " << encoder_data->pos_m << std::endl; 
    // std::cout << "Motor Velocity: " << encoder_data->vel_m << std::endl; 
    // std::cout << "Motor Manufacturer Reg: " << encoder_data->manufacturer_reg_m << std::endl; 
    // std::cout << "Motor Latched Fault: " << encoder_data->latched_fault_m << std::endl; 
    
    
};


void EncoderSensor::updateData(){

    
    while(true){
        std::unique_lock<std::mutex> lk(read_mutex_);
        std::cout << "Waiting... \n";

        cv.wait(lk, [this] { return message_received; });
        std::cout << "...finished waiting \n";

        message_received = false;

        lk.unlock();
    }

}

void EncoderSensor::readMotorData(){

    
    while(true){
    
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        {
            std::lock_guard<std::mutex> lk(read_mutex_);

            

            readData(motor_id_, &encoder_data_);

            if(read_err_ == 0){
                message_received = true;
            }

            
        }
        cv.notify_one();
    }

}

void EncoderSensor::getData(Json::Value &sensor_data){
    
    read_mutex_.lock();

    sensor_data["counts"] = sensor_data_["counts"];
    sensor_data["state"] = sensor_data_["state"];
    
    std::cout<< "Data Read Sensor 1" <<std::endl;
    
    read_mutex_.unlock();
}
