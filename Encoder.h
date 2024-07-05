// Motor Encoder Module Header File

#ifndef __MOTOR_ENCODER_H
#define __MOTOR_ENCODER_H

#include "stm32f303xe.h"
#include "utility.h"


#define ENCODER_PORT A

#define ENCODER_TIMER			TIM2
#define ENCODER_TIMER_INT	TIM2_IRQn

#define LEFT_ENCODER_CH		CCR1
#define LEFT_ENCODER_PIN 	0  //PA0

#define RIGHT_ENCODER_CH	CCR2
#define RIGHT_ENCODER_PIN	1  //PA1

#define LEFT_ENC	0
#define RIGHT_ENC 1

void Encoder_Init(void);

// Helper Function for Debugging
uint32_t getEncoderCHValue( uint8_t enc);

extern uint32_t leftEncoderPeriod;
extern uint32_t rightEncoderPeriod;


#endif
