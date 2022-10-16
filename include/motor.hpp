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

    public:
    Motor();
    ~Motor();
    typedef std::shared_ptr<Motor> MotorSPtr;
    typedef std::unique_ptr<Motor> MotorUPtr;

    bool motor_init(int motor_id);
    int motor_config_node(int motor_id);
    int motor_Transmit_PDO_n_Parameter(uint16_t node_id, uint8_t n, uint32_t cob);
    int motor_Transmit_PDO_n_Mapping(uint16_t node_id, uint8_t n, uint8_t num_objects, Epos_pdo_mapping* objects);

    Sockets::SocketsSPtr motor_sockets = std::make_shared<Sockets>();
    
};

#endif