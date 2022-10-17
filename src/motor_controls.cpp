#include <motor_controls.hpp>

MotorControls::MotorControls(){
    
}

MotorControls::~MotorControls(){
    
}

int MotorControls::motor_rpm_to_cps(float rpm){
    int m_cps= rpm * DRIVING_MOTOR_RPM_TO_COUNTS_PER_SEC;
	return m_cps;
}


int MotorControls::motor_rps2_to_cps2(float rpss) // RPS2 to 10 counts/sec2 conversion
{
	int m_cps2 = rpss * MOTOR_ACC_MULTIPLIER;
	return m_cps2;
}

int MotorControls::set_vel_speed(float vel, uint16_t nodeid){
    int err = 0;
	const int32_t rpm = motor_rpm_to_cps(vel) ;
	Socketcan_t target_vel[2] = {
		{2, Switch_On_And_Enable_Operation},
		{4, rpm}};

	err = PDO_send(motor_sockets->motor_vel_pdo_fd, PDO_RX4_ID + nodeid, 2, target_vel);
	return err;
}

int MotorControls::set_profile_velocity(uint16_t node_id,uint32_t speed) {
	int err = 0;

	SDO_data d;
	d.nodeid = node_id;
	d.index = 0x6081;
	d.subindex = 0x00;
	d.data.size = 4;
	d.data.data = speed;//in milliseconds
	err |= SDO_write(motor_sockets->motor_cfg_fd, &d);

	return err;
}

int MotorControls::set_profile_acc(uint16_t node_id,uint32_t acc) {
	int err = 0;

	SDO_data d;
	d.nodeid = node_id;
	d.index = 0x6083;
	d.subindex = 0x00;
	d.data.size = 4;
	d.data.data = acc;//in milliseconds
	err |= SDO_write(motor_sockets->motor_cfg_fd, &d);

	return err;
}

int MotorControls::set_profile_deacc(uint16_t node_id,uint32_t deacc) {
	int err = 0;

	SDO_data d;
	d.nodeid = node_id;
	d.index = 0x6084;
	d.subindex = 0x00;
	d.data.size = 4;
	d.data.data = deacc;//in milliseconds
	err |= SDO_write(motor_sockets->motor_cfg_fd, &d);

	return err;
}

int MotorControls::set_driving_motor_position_mode_params(uint16_t node_id,float position_mode_acc, float position_mode_deacc, float position_mode_speed){
	int err = 0;
    err |= set_profile_velocity(node_id,motor_rpm_to_cps(position_mode_speed) / DRIVING_MOTOR_REGISTER_MULTIPLIER); 
	err |=set_profile_acc(node_id,motor_rps2_to_cps2(position_mode_acc));
	err |=set_profile_deacc(node_id,motor_rps2_to_cps2(position_mode_deacc));
    return err;
}

bool MotorControls::motor_command(std::string motor_name, std::string command_type, position_cmd_t position, velocity_cmd_t velocity){
    
    if (command_type =="velocity"){

    }

    if (command_type =="position"){

    }
}
    