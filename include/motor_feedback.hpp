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
    MotorFeedback();
    ~MotorFeedback();

    typedef std::shared_ptr<MotorFeedback> MotorFeedbackSPtr;
    typedef std::unique_ptr<MotorFeedback> MotorFeedbackUPtr;

    Sockets::SocketsSPtr motor_sockets = std::make_shared<Sockets>();

    int motor_status_n_voltage_read(int motor_id, uint16_t *status, float *battery_vol, int timeout);
    int motor_enc_read(int motor_id, uint32_t *pos, int timeout);
    double motor_cps_to_rpm(double counts_per_sec);
    int motor_vel_read(int motor_id, double *vel, int timeout);
    int motor_system_status_read(int motor_id, uint32_t *manufacturer_reg, uint32_t *latched_fault, int timeout);
    
};

#endif