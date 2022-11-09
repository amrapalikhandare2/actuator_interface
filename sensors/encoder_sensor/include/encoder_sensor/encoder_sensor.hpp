#ifndef ENCODER_SENSOR_H_
#define ENCODER_SENSOR_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <json_reader/json_read.h>
#include <sensor/sensor.hpp>
#include <sockets.hpp>
#include <motor_feedback.hpp>
#include <queue>
#include <condition_variable>

class EncoderData {

    public:

    EncoderData() = default;

    ~EncoderData() = default;

    uint16_t status_m; 
    float battery_vol_m;
    int32_t pos_m; 
    double vel_m;
    uint32_t manufacturer_reg_m;
    uint32_t latched_fault_m;

};

class EncoderSensor : public Sensor{

    public:

        typedef std::shared_ptr<EncoderSensor> EncoderSensorSPtr;
        typedef std::unique_ptr<EncoderSensor> EncoderSensorUPtr;
        
        EncoderSensor(int motor_id, Sockets::SocketsSPtr motor_sockets);
        ~EncoderSensor();
        
        void getData(Json::Value &sensor_data);  
        std::shared_ptr<spdlog::logger> logger_;

        std::thread update_data_thread_;
        std::thread read_motor_data_thread_;
        void readMotorData();
        Json::Value sensor_data_;
        std::mutex read_mutex_;
        void init_json();
        int motor_id_;
        EncoderData encoder_data_;
        MotorFeedback::MotorFeedbackSPtr motor_feedback_;
        bool message_received;
        void updateData();
        int read_err_;
        void readData(int motor_id, EncoderData *encoder_data);
        MotorFeedback::feedback_s feedback_s_m_;
        std::condition_variable cv;
        
        
        // std::queue<> q_encoder_data_;
        
};

#endif // ENCODER_SENSOR_H_