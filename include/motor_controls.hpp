#ifndef MOTOR_CONTROLS_HPP_
#define MOTOR_CONTROLS_HPP_


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <iostream>
#include <sockets.hpp>
#include <motor_params.hpp>

#include "../canopen/canopen.h"

class MotorControls{

    private:
    std::string motor_name;
    int motor_id;
    int motor_axis;
    std::shared_ptr<spdlog::logger> logger_;

    typedef struct {
        uint16_t index;
        uint8_t subindex;
        uint8_t length;
    } Epos_pdo_mapping;

    enum Epos_ctrl {
        Shutdown = 0x06,
        Switch_On = 0x07,
        Switch_On_And_Enable_Operation = 0x0f,
        Disable_Voltage = 0x00,
        Quickstop = 0x02,
        Disable_Operation = 0x07,
        Enable_Operation = 0x0f,
        Position_Trigger = 0x5f,
        Reset_Fault = 0x80,
    };

    enum Motor_mode {
        Motor_mode_Velocity = 3,
        Motor_mode_Position = 1,
            Motor_mode_Interpolated_Position_Mode = 7,
        Motor_mode_Homing_Mode = 6,
            Motor_mode_Position_Mode = -1,
        Motor_mode_Velocity_Mode = -2,
        Motor_mode_Current_Mode = -3,
        Motor_mode_Diagnostic_Mode = -4,
        Motor_mode_Master_Encoder_Mode = -5,
        Motor_mode_Step_Direction_Mode = -6
    };

    public:
    MotorControls();
    ~MotorControls();

    typedef std::shared_ptr<MotorControls> MotorControlsSPtr;
    typedef std::unique_ptr<MotorControls> MotorControlsUPtr;

    Sockets::SocketsSPtr motor_sockets = std::make_shared<Sockets>();

    typedef struct velocity_cmd_ {
        double timeout;
        double velocity;
        double max_vel; // position loop params
        double accel;
        double decel;
    }velocity_cmd_t;

    typedef struct position_cmd_ {
        double timeout;
        double relative_pos;
        double max_vel;
        double accel;
        double decel;
    }position_cmd_t;

    typedef union md_control_register_s_ {
        struct control_s_
        {
            uint16_t switch_on:1;
            uint16_t enable_voltage:1;
            uint16_t quick_stop:1;
            uint16_t enable_operation:1;
            uint16_t new_setpoint:1;
            uint16_t instantaneous_change_set:1;
            uint16_t absolute_or_relative:1;                    // 0 is absolute, 1 is relative
            uint16_t reset_fault:1;
            uint16_t halt:1;
            uint16_t reserved:7;
        }control_s;

        uint16_t control_word;
    }md_control_register_u_t;

    md_control_register_u_t md_control_register = {0};

    // velocity_cmd_t velocity_cmd_element;
    // position_cmd_t position_cmd_element;

    bool motor_command(int motor_id, std::string command_type, position_cmd_t position_cmd_element, velocity_cmd_t velocity_cmd_element);
    
    int set_vel_speed(uint16_t nodeid, int axis, float vel);
    int set_relative_position(uint16_t node_id, int axis, uint32_t position);

    int motor_rpm_to_cps(float rpm);
    int motor_rps2_to_cps2(float rpss);

    int set_profile_velocity(uint16_t node_id,uint32_t speed);

    int set_profile_acc(uint16_t node_id,uint32_t acc);

    int set_profile_deacc(uint16_t node_id,uint32_t deacc);

    int set_driving_motor_position_mode_params(uint16_t node_id,double position_loop_acc, double position_loop_deacc, double position_loop_speed);
    
};

#endif