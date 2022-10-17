#include <motor.hpp>
#include <sockets.hpp>

Motor::Motor(){
    
}

Motor::~Motor(){
    
}

int Motor::motor_Transmit_PDO_n_Parameter(uint16_t node_id, uint8_t n, uint32_t cob){
    SDO_data d;
	d.nodeid = node_id;
	d.index = 0x1800 + n-1;
	d.subindex = 0x02;
	d.data.size = 1;
	d.data.data = 0x01;
	return SDO_write(motor_sockets->motor_cfg_fd, &d);
}

int Motor::motor_Transmit_PDO_n_Mapping(uint16_t node_id, uint8_t n, uint8_t num_objects, Epos_pdo_mapping* objects) {
    int err = 0;

	// Set number of objects to zero
	SDO_data d;
	d.nodeid = node_id;
	d.index = 0x1A00 + n-1;
	d.subindex = 0x00;
	d.data.size = 1;
	d.data.data = 0;

	err = SDO_write(motor_sockets->motor_cfg_fd, &d);
	if (err != 0) {
		return err;
	}

	// Write objects
	d.data.size = 4;
	for(int i=0; i<num_objects; i++) {
		Epos_pdo_mapping obj = objects[i];

		d.subindex = i+1;
		d.data.data = ((uint32_t)obj.index << 16) | (obj.subindex<<8) | (obj.length);
		err = SDO_write(motor_sockets->motor_cfg_fd, &d);
		if (err != 0) {
			return err;
		}
	}

	// Set Correct number of objects
	d.subindex = 0x00;
	d.data.size = 1;
	d.data.data = num_objects;

	return SDO_write(motor_sockets->motor_cfg_fd, &d);

}

int Motor::motor_config_node(int motor_id){
    int err;
    int num_PDOs;
    err |= motor_Transmit_PDO_n_Parameter(motor_id, 1, PDO_TX1_ID + motor_id);
	err |= motor_Transmit_PDO_n_Parameter(motor_id, 2, PDO_TX2_ID + motor_id);
	err |= motor_Transmit_PDO_n_Parameter(motor_id, 3, PDO_TX3_ID + motor_id);
	err |= motor_Transmit_PDO_n_Parameter(motor_id, 4, PDO_TX4_ID + motor_id);	
	
    // PDO TX1 Statusword and High Voltage Reference
	num_PDOs = 2;
	Epos_pdo_mapping status_and_vol[] = {
		{0x6041, 0x00, 16},   // Statusword
		{0x2201, 0x00, 16}   // High Voltage Reference
	};
	err |= motor_Transmit_PDO_n_Mapping(motor_id, 1, num_PDOs, status_and_vol);
	
    // PDO TX2 velocity
	num_PDOs = 1;
	Epos_pdo_mapping vel[] = {
		{0x606C, 0x00, 32} // Speed feedback
	};
	err |= motor_Transmit_PDO_n_Mapping(motor_id, 2, num_PDOs, vel);

	// PDO TX3 Encoder Counts
	num_PDOs = 1;
	Epos_pdo_mapping enc[] = {
		{0x6064, 0x00, 32}, // Position Actual value
	};
	err |= motor_Transmit_PDO_n_Mapping(motor_id, 3, num_PDOs, enc);

	// PDO TX4 Manufacturer Status and Latched Fault
	num_PDOs = 2;
	Epos_pdo_mapping manufacturer_status[] = {
		{0x1002, 0x00, 32},   // Manfa Statusword
		{0x2183, 0x00, 32}    // Latching Fault Status Register
	};
	err |= motor_Transmit_PDO_n_Mapping(motor_id, 4, num_PDOs, manufacturer_status);

    err |= motor_Transmit_PDO_n_Mapping(motor_id, 5, 0, NULL);
	err |= motor_Transmit_PDO_n_Mapping(motor_id, 6, 0, NULL);
	err |= motor_Transmit_PDO_n_Mapping(motor_id, 7, 0, NULL);

}

int Motor::motor_setmode_sdo(uint16_t motor_id, enum Motor_mode mode){
    int err = 0;

    SDO_data d;
	d.nodeid = motor_id;
	d.index = 0x6060;
	d.subindex = 0x00;
	d.data.size = 1;
	d.data.data = mode;

	return SDO_write(motor_sockets->motor_cfg_fd, &d);
}

int Motor::set_guard_time(uint16_t motor_id, uint16_t value) {
	SDO_data d;
	d.nodeid = motor_id;
	d.index = 0x100C;
	d.subindex = 0x00;
	d.data.size = 2;
	d.data.data = value;

	return SDO_write(motor_sockets->motor_cfg_fd, &d);

}

int Motor::set_life_time_factor(uint16_t motor_id, uint8_t value) {
	SDO_data d;
	d.nodeid = motor_id;
	d.index = 0x100D;
	d.subindex = 0x00;
	d.data.size = 1;
	d.data.data = value;

	return SDO_write(motor_sockets->motor_cfg_fd, &d);

}

bool Motor::motor_init(int motor_id){
    
    int err = 0;

    err |= NMT_change_state(motor_sockets->nmt_motor_cfg_fd, CANOPEN_BROADCAST_ID, NMT_Enter_PreOperational);
	if (err != 0)
	{
		return MOTOR_ERROR;
	}

    err |= motor_config_node(motor_id);
    if (err != 0)
	{
		return MOTOR_ERROR;
	}

    //setting default mode
    err |= motor_setmode_sdo(motor_id,Motor_mode_Velocity);
	if (err != 0)
	{
		return MOTOR_ERROR;
	}

    set_guard_time(motor_id,50);
	set_life_time_factor(motor_id,4);

}