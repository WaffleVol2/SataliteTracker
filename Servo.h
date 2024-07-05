//Servo Module Header File

#include "stm32f303xe.h"
#include "utility.h"

#define RC_SERVO_PIN 	(15)
#define ARR_VALUE			(20000-1)	// 20ms PWM frequency

#define CENTREPERIOD	1500UL  //centre position
#define PW_MIN				600UL 	//-90 deg
#define PW_MAX				2400UL	//+90 deg

#define SERVO_ANGLE_MIN		-45
#define SERVO_ANGLE_MAX		 45
#define SERVO_ANGLE_STEP	  5

void RCServo_Init(void);
uint16_t RCServo_SetAngle( int16_t angle );
