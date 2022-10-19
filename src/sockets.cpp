#include <sockets.hpp>

Sockets::Sockets(int motor_id){
    createSockets(motor_id);
}

Sockets::~Sockets(){
    
}

bool Sockets::createSockets(int motor_id){

    uint32_t motor_status_pdo_masks[1] = {COB_MASK};
	uint32_t motor_status_pdo_filters[1] = {
		PDO_TX1_ID + motor_id,
		};
	motor_status_pdo_fd = socketcan_open(motor_status_pdo_filters, motor_status_pdo_masks, 1);
	std::cout << motor_status_pdo_fd<< std::endl;

    uint32_t motor_vel_pdo_masks[1] = {COB_MASK};
	uint32_t motor_vel_pdo_filters[1] = {
		PDO_TX2_ID + motor_id,
		};
	motor_vel_pdo_fd = socketcan_open(motor_vel_pdo_filters, motor_vel_pdo_masks, 1);

    uint32_t motor_enc_pdo_masks[1] = {COB_MASK};
	uint32_t motor_enc_pdo_filters[1] = {
		PDO_TX3_ID + motor_id,
		};
	motor_enc_pdo_fd = socketcan_open(motor_enc_pdo_filters, motor_enc_pdo_masks, 1);

    uint32_t motor_system_status_pdo_masks[1] = {COB_MASK};
	uint32_t motor_system_status_pdo_filters[1] = {
		PDO_TX4_ID + motor_id,
		};
	motor_system_status_pdo_fd =  socketcan_open(motor_system_status_pdo_filters, motor_system_status_pdo_masks, 1);
	
    uint32_t cfg_masks[2] = {COB_MASK, COB_MASK}; 
	uint32_t cfg_filters[2] = {
		0x00,
		SDO_TX + motor_id
        };
	motor_cfg_fd = socketcan_open(cfg_filters, cfg_masks, 3);

    uint32_t nmt_cfg_masks[1] = {COB_MASK};
	uint32_t nmt_cfg_filters[1] = {
		NMT_TX + motor_id};
	nmt_motor_cfg_fd = socketcan_open(nmt_cfg_filters, nmt_cfg_masks, 1);

    uint32_t sync_masks[1] = {COB_MASK};
	uint32_t sync_filters[1] = {
		SYNC_TX};
	motor_sync_fd = socketcan_open(sync_filters, sync_masks, 1);

    if (motor_status_pdo_fd == -1 || motor_vel_pdo_fd == -1 || motor_enc_pdo_fd == -1 || motor_system_status_pdo_fd == -1 
    || motor_cfg_fd == -1 || nmt_motor_cfg_fd == -1 || motor_sync_fd == -1  )
	{
		return SOCKETS_ERROR;
	}
	return 0;
}