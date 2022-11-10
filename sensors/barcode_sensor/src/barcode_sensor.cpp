#include <barcode_sensor/barcode_sensor.hpp>

using namespace std;


BarcodeSensor::BarcodeSensor(int barcode_id, int barcode_base_id) {
    // logger_ = spdlog::get("controller_manager")->clone("dummy_sensor_2");

    // init_json();

    barcode_id_ = barcode_id;
    read_barcode_data_thread_ = std::thread(&BarcodeSensor::readBarcodeData,this);
    update_data_thread_ = std::thread(&BarcodeSensor::updateData, this);
    gls_barcode_ = std::make_shared<GlsBarcode>(barcode_id_, barcode_base_id);
    gls_barcode_->gls_init(barcode_id_);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    gls_barcode_->gls_enable(barcode_id_);

    read_err_ = 0;
    message_received = false;
}

BarcodeSensor::~BarcodeSensor() {

    update_data_thread_.join();
    read_barcode_data_thread_.join();
}

void BarcodeSensor::init_json() {

    JsonRead parser(
            "/application/rightbot_ws/src/actuator_interface/sensors/barcode_sensor/config/read_data.json");

    if (!parser.parse())
        throw std::invalid_argument("Parsing error in Barcode Sensor");

    parser.getValue(sensor_data_);
}

void BarcodeSensor::readData(){

    read_err_ =  gls_barcode_->barcodeFeedback(barcode_id_, &feedback_s_b_);

}

void BarcodeSensor::updateData() {

    while(true){
        std::unique_lock<std::mutex> lk(read_mutex_);
        //std::cout << "Waiting... \n";

        cv.wait(lk, [this] { return message_received; });
        //std::cout << "...finished waiting \n";

        message_received = false;

        lk.unlock();
    }
}

void BarcodeSensor::readBarcodeData(){

    
    while(true){
    
        std::this_thread::sleep_for(std::chrono::milliseconds(5));

        {
            std::lock_guard<std::mutex> lk(read_mutex_);

            readData();

            if(read_err_ == 0){
                message_received = true;
                q_barcode_data_.push(feedback_s_b_);
            }
            
        }
        cv.notify_one();
    }

}


void BarcodeSensor::getData(Json::Value &sensor_data) {

    read_mutex_.lock();

    if(!q_barcode_data_.empty()){
        encoder_barcode_q_element_ = q_barcode_data_.front();
        q_barcode_data_.pop();
    }

    sensor_data["x"] = encoder_barcode_q_element_.x_b;
    sensor_data["y"] = encoder_barcode_q_element_.y_b;
    sensor_data["ang"] = encoder_barcode_q_element_.ang_b;
    sensor_data_["sensor_time"] = static_cast<uint32_t>(encoder_barcode_q_element_.sensor_time_b);
    sensor_data_["decode_time"] = static_cast<uint32_t>(encoder_barcode_q_element_.decode_time_b);
    sensor_data_["tag_x"] = static_cast<uint32_t>(encoder_barcode_q_element_.tag_x_b);
    sensor_data_["tag_y"] = static_cast<uint32_t>(encoder_barcode_q_element_.tag_y_b);

    // logger_->debug("Data Read Sensor 2");


    read_mutex_.unlock();
}
