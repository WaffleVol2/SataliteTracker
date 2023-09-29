#include "stm32f303xe.h"
#include "LED.h"
#include "LCD.h"
#include "SysClock.h"
#include "UART.h"
#include "Stepper.h"
#include "utility.h"
#include "RCServo.h"
#include "ultraSonicInit.h"
#include "DriveMotor.h"

int main(void)
{
	RCServo_Init();
	UART2_INIT();
	UART2_Config();
	//LED_INIT();
	Stepper_Init();
	//LCD_Init();
	//ultraSonicInit();
	UARTprintf(" Stepper Demo\n__________________\n0: Stop\n1: Clockwise Full Step\n2: Counter Clockwise Full Step\n3: Clockwise Half Step\n4: Counter Clockwise Half Step\nCMD: \n");
	int8_t stepType;
	char holderLab3;
	int16_t defaultAngle = 90;
	char holder;
	char input = 'ZZZ';
	char inputCommand = '\0';
	DriveMotor_Init();
	
	
//	//MOTOR START
//	for(;;)
//	{

//				inputCommand = UARTgetcND();
//		switch( inputCommand )
//		{
//			case 'y': // L FWD
//				SetMotorSpeed(LEFT_MOTOR, 750);
//				SetMotorDir(LEFT_MOTOR, MOTOR_FWD);
//				break;
//				
//			case 'h': // L STOP
//				SetMotorSpeed(LEFT_MOTOR, 0);
//				SetMotorDir(LEFT_MOTOR, MOTOR_STOP);
//				break;
//			
//			case 'n': // L RWD
//				SetMotorSpeed(LEFT_MOTOR, 250);
//				SetMotorDir(LEFT_MOTOR, MOTOR_RWD);
//				break;
//			
//			case 'u': // R FWD
//				SetMotorSpeed(RIGHT_MOTOR, 750);
//				SetMotorDir(RIGHT_MOTOR, MOTOR_FWD);
//				break;
//			
//			case 'j': // R STOP
//				SetMotorSpeed(RIGHT_MOTOR, 0);
//				SetMotorDir(RIGHT_MOTOR, MOTOR_STOP);
//				break;
//			
//			case 'm': // R RWD
//				SetMotorSpeed(RIGHT_MOTOR, 250);
//				SetMotorDir(RIGHT_MOTOR, MOTOR_RWD);
//				break;
//										
//			default:				
//				break;
//			}
//			
//			
//		}		
//		
	
	//LCD
		//
	//	holder = UARTgetcND();
		//if (holder != '\0'){
	//		input = holder;
		//	LCDputs();
		//	LCDprintf("Test");
		//	UARTprintf("Character is: %c", input);
		//}
	
	//lab 3
//	for(;;){
//	RCServo_SetAngle(defaultAngle);
//	holderLab3 = UARTgetcND();
//		if (holderLab3 == 'i'){
//			defaultAngle += 3;
//			RCServo_SetAngle(defaultAngle);
//		}
//		else if (holderLab3 == 'k'){
//			defaultAngle -= 3;
//			RCServo_SetAngle(defaultAngle);
//		}
////		
////	
////	
//}
	// ends here
	
	
	//PROGRAM LOOP
	//ultrasonic starts'
//	ultraSonicInit();
//	while (1) {
//    // check if a key is pressed to start a distance measurement
//		holder = UARTgetcND();
//    if (holder == 's') {
//        // fire the trigger function to send a pulse to the sensor
//			UARTprintf("firing sensor");
//			ON_DEMAND_TRIGGER();

//       // READ_SENSOR();
//    }
//    // check if ECHO has been received
//    if (ECHO_RECEIVED()) {
//        // acquire the measured distance from the sensor
//        uint32_t distance = READ_SENSOR();
//			UARTprintf("ECHO RECIEVED HAPPENED %d", distance);
//			//READ_SENSOR();
//        // do something with the distance, e.g. display it on an LCD or send it over UART
//        // reset the flag to indicate that a new measurement can be taken
//        TIM3->SR &= ~TIM_SR_CC1IF;
//    }
//    // do other stuff if ECHO has not been received yet
//    else {
//		UARTprintf("\n no echo received\n");

//        // do some other task, e.g. check for user input or update a display
//    }
//}
	//ultrasonic ends
	for(;;) //same as while (1)
	{
		
		holder = UARTgetcND();
		if (holder != '\0'){
			input = holder;
		}
		
		
		switch(input)
		{
			case '0':
				stepType = STEPPER_STEP_STOP;
			UARTprintf("\nCMD STOP\n");
			break;
			
			case '1':
				stepType = STEPPER_STEP_CW_FULL;
			UARTprintf("CMD CW F\n");
			break;
			
			case '2':
				stepType = STEPPER_STEP_CCW_FULL;
			UARTprintf("CMD CCW F\n");
			break;
			
			case '3':
				stepType = STEPPER_STEP_CW_HALF;
			UARTprintf("CMD CW H\n");
			break;
			
			case '4':
				stepType = STEPPER_STEP_CCW_HALF;
			UARTprintf("CMD CCW H\n");
			break;
			
			default:
				break;
		}
		Stepper_Step(stepType);
		UARTprintf("Number: %d", stepType);
		
		
		Delay_ms(50);
		TOGGLE();
	}
}
