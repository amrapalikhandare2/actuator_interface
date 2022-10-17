#ifndef MOTOR_HPP_
#define MOTOR_HPP_


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <iostream>

#include "../canopen/canopen.h"
#include <sockets.hpp>
# define MOTOR_ERROR (-1)

class Motor{

    private:
    std::string motor_name;
    int motor_id;
    std::shared_ptr<spdlog::logger> logger_;
    typedef struct {
        uint16_t index;
        uint8_t subindex;
        uint8_t length;
    } Epos_pdo_mapping;

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
    Motor();
    ~Motor();
    typedef std::shared_ptr<Motor> MotorSPtr;
    typedef std::unique_ptr<Motor> MotorUPtr;

    bool motor_init(int motor_id);
    int motor_config_node(int motor_id);
    int motor_Transmit_PDO_n_Parameter(uint16_t node_id, uint8_t n, uint32_t cob);
    int motor_Transmit_PDO_n_Mapping(uint16_t node_id, uint8_t n, uint8_t num_objects, Epos_pdo_mapping* objects);
    int motor_setmode_sdo(uint16_t motor_id, enum Motor_mode mode);
    int set_guard_time(uint16_t motor_id, uint16_t value);
    int set_life_time_factor(uint16_t motor_id, uint8_t value);

    Sockets::SocketsSPtr motor_sockets = std::make_shared<Sockets>();
    
};

#endif