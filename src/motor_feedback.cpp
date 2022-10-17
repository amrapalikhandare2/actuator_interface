#include <motor_feedback.hpp>


MotorFeedback::MotorFeedback(){
    
}

MotorFeedback::~MotorFeedback(){
    
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

int MotorFeedback::motor_enc_read(int motor_id, int32_t *pos, int timeout)
{

	int err;

	my_can_frame f;
	err = PDO_read(motor_sockets->motor_enc_pdo_fd, &f, timeout);


	uint32_t enc;
	if (f.id == (PDO_TX3_ID + motor_id))
	{

	//ENCODER COUNT OF LEFT
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
