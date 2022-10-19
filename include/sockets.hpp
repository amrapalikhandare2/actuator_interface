#ifndef SOCKETS_HPP_
#define SOCKETS_HPP_


#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <iostream>

#include "../canopen/canopen.h"

#define SOCKETS_ERROR   (-1)

class Sockets{

    private:
    std::string motor_name;
    int motor_id;
    std::shared_ptr<spdlog::logger> logger_;

    public:
    Sockets(int motor_id);
    ~Sockets();

    bool createSockets(int motor_id);
    typedef std::shared_ptr<Sockets> SocketsSPtr;
    typedef std::unique_ptr<Sockets> SocketsUPtr;

    int motor_pdo_fd = -1;	//!< Process CAN-connection.
    int motor_cfg_fd = -1;	//!< Configuration CAN-connection.
    int motor_sync_fd = -1;  //!< Sync CAN-connection.

    int nmt_motor_cfg_fd = -1;

    int motor_status_pdo_fd = -1;
    int motor_vel_pdo_fd = -1;
    int motor_enc_pdo_fd = -1; 
    int motor_system_status_pdo_fd = -1;


    
};

#endif