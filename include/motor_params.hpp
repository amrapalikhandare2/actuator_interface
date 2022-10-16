#ifndef PHYSICS
#define PHYSICS
#include <inttypes.h>

/*** CAN-bus spesific ***/
#define MOTOR_EPOS_LEFT_FRONT_ID 0x0C
#define MOTOR_EPOS_RIGHT_FRONT_ID 0x0D
#define MOTOR_EPOS_LEFT_REAR_ID 0x0E
#define MOTOR_EPOS_RIGHT_REAR_ID 0X0F

/*** Errors ***/
#define MOTOR_ERROR   (-1)
#define MOTOR_TIMEOUT (-2)

#endif // LIBMOTOR_H
