#ifndef MOTOR_FEEDBACK_HPP_
#define MOTOR_FEEDBACK_HPP_


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <iostream>
#include <sockets.hpp>
#include <motor_params.hpp>

class MotorFeedback{

    private:
    std::string motor_name;
    int motor_id;
    std::shared_ptr<spdlog::logger> logger_;

    bool init_enc = false ;
    uint32_t err_enc = 0; 

    public:
    MotorFeedback(Sockets::SocketsSPtr motor_sockets_);
    ~MotorFeedback();

    typedef std::shared_ptr<MotorFeedback> MotorFeedbackSPtr;
    typedef std::unique_ptr<MotorFeedback> MotorFeedbackUPtr;

    Sockets::SocketsSPtr motor_sockets;

    typedef struct feedback_ {
        uint16_t status_m; 
        float battery_vol_m;
        uint32_t pos_m; // position loop params
        double vel_m;
        uint32_t manufacturer_reg_m;
        uint32_t latched_fault_m;
    }feedback_s;



    int motor_status_n_voltage_read(int motor_id, uint16_t *status, float *battery_vol, int timeout);
    int motor_enc_read(int motor_id, uint32_t *pos, int timeout);
    double motor_cps_to_rpm(double counts_per_sec);
    int motor_vel_read(int motor_id, double *vel, int timeout);
    int motor_system_status_read(int motor_id, uint32_t *manufacturer_reg, uint32_t *latched_fault, int timeout);

    uint16_t status_register_fb_[1] = {0};
    float battery_vol_fb_[1] = {0};
    uint32_t encoder_fb_[1] = {0};
    double vel_fb_[1] = {0};
    uint32_t manufacturer_reg_fb_[1] = {0};
    uint32_t latched_fault_fb_[1] = {0};

    int motor_request(void);
    int motorFeedback(int motor_id, MotorFeedback::feedback_s *feedback_s_m);
    
};

#endif