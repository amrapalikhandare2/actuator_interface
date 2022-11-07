#ifndef ENCODER_SENSOR_H_
#define ENCODER_SENSOR_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <json_reader/json_read.h>
#include <sensor/sensor.hpp>
#include <sockets.hpp>

class EncoderData {

    public:

    EncoderData() = default;

    ~EncoderData() = default;

    uint16_t status_m; 
    float battery_vol_m;
    uint32_t pos_m; // position loop params
    double vel_m;
    uint32_t manufacturer_reg_m;
    uint32_t latched_fault_m;

};

class EncoderSensor : public Sensor{

    public:

        typedef std::shared_ptr<EncoderSensor> EncoderSensorSPtr;
        typedef std::unique_ptr<EncoderSensor> EncoderSensorUPtr;
        
        EncoderSensor(Sockets::SocketsSPtr motor_sockets);
        ~EncoderSensor();
        
        void getData(Json::Value &sensor_data);  

        std::thread update_data_thread_;
        void updateData();
        Json::Value sensor_data_;
        std::mutex read_mutex_;
        void init_json();
        EncoderData encoder_data_;

        
};

#endif // ENCODER_SENSOR_H_