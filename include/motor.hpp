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
        
    };

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
    int motor_enable(int motor_id);

    Sockets::SocketsSPtr motor_sockets = std::make_shared<Sockets>();
    
};

#endif