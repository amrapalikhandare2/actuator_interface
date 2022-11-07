#include <motor_feedback.hpp>


MotorFeedback::MotorFeedback(Sockets::SocketsSPtr motor_sockets_){
    motor_sockets = motor_sockets_ ;
}

MotorFeedback::~MotorFeedback(){
    
}

double MotorFeedback::motor_cps_to_rpm(double counts_per_sec)
{
	
	double m_per_sec = (counts_per_sec) * DRIVING_MOTOR_COUNTS_PER_SEC_TO_RPM;
	return m_per_sec;
}

int MotorFeedback::motor_status_n_voltage_read(int motor_id, uint16_t *status, float *battery_vol, int timeout){
    int err;
	my_can_frame f;
	err = PDO_read(motor_sockets->motor_status_pdo_fd, &f, timeout);

	if (f.id == (PDO_TX1_ID + motor_id)){
        *status = (f.data[0]<<0) | (f.data[1]<<8);
        *battery_vol = (f.data[2]<<0) | (f.data[3]<<8);
        *battery_vol = 0.1 * (*battery_vol);
    }
	
	return err;

}

int MotorFeedback::motor_enc_read(int motor_id, uint32_t *pos, int timeout)
{
	int err;
	my_can_frame f;
    uint32_t enc;

	err = PDO_read(motor_sockets->motor_enc_pdo_fd, &f, timeout);

	if (f.id == (PDO_TX3_ID + motor_id))
	{
	    //ENCODER COUNT
		enc = ((uint32_t)f.data[0] << 0) | ((uint32_t)f.data[1] << 8) | ((uint32_t)f.data[2] << 16) | ((uint32_t)f.data[3] << 24);
		//rpm = ((uint32_t)f.data[4]<<0) | ((uint32_t)f.data[5]<<8) | ((uint32_t)f.data[6]<<16) | ((uint32_t)f.data[7]<<24);
		if (init_enc)
		{
			*pos = -enc - err_enc;
		}
		else
		{
			err_enc = -enc;
			init_enc = true;
		}
		//*vel = rpm*0.1;//motor_rpm_to_mmsec(-rpm);
	}

	return err;
}

int MotorFeedback::motor_vel_read(int motor_id, double *vel, int timeout)
{
	int err;
	my_can_frame f;
    int32_t rpm;
	int32_t register_cps;
	double cps;

	err = PDO_read(motor_sockets->motor_vel_pdo_fd, &f, timeout);
	
	if (f.id == (PDO_TX2_ID + motor_id))
	{
	    //RPM OF LEFT 
		register_cps = ((uint32_t)f.data[0] << 0) | ((uint32_t)f.data[1] << 8) | ((uint32_t)f.data[2] << 16) | ((uint32_t)f.data[3] << 24);
		cps = register_cps;
		*vel = (double)motor_cps_to_rpm(cps);
	}

	return err;
}

int MotorFeedback::motor_system_status_read(int motor_id, uint32_t *manufacturer_reg, uint32_t *latched_fault, int timeout)
{

	int err;
	my_can_frame f;
	err = PDO_read(motor_sockets->motor_system_status_pdo_fd, &f, timeout);

	if (f.id == (PDO_TX4_ID + motor_id))
	{
	    //STATUS OF LEFT MOTOR
        *manufacturer_reg = ((uint32_t)f.data[0] << 0) | ((uint32_t)f.data[1] << 8) | ((uint32_t)f.data[2] << 16) | ((uint32_t)f.data[3] << 24);
		*latched_fault = ((uint32_t)f.data[4] << 0) | ((uint32_t)f.data[5] << 8) | ((uint32_t)f.data[6] << 16) | ((uint32_t)f.data[7] << 24);
    }

	return err;
}
