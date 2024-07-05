// Servo Module Source

#include "Servo.h"

void RCServo_Init(void)
{
	
	// Turning on GPIO PB15 for TIM15 PWM
	
	RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
	
	//GPIOB -> MODER &= ~( 0x03UL << (15*2) );  //reset PB15 mode
	//GPIOB -> MODER !=  ( 0x02UL << (15*2) );  //set PB15 mode to AF
		// Now can also use...
	GPIO_MODER_SET(B, RC_SERVO_PIN, 2UL); // 10 is AF
	
	
	//GPIOB -> AFR[1] |= ( 0x01UL << GPIO_AFRH_AFRH7_Pos ); // Set PB15 to AF1 (TIM15 Channel 2, Non-Negated)
		// now can also use...
	FORCE_BITS( GPIOB -> AFR[1], GPIO_AFRH_AFRH7_Msk, 0x1UL << GPIO_AFRH_AFRH7_Pos );
	
	
	//GPIOB -> OTYPER &= ~ ( 0x1UL << 15 ); // Push-pull for PB15
		// now can also use...
	GPIO_OTYPER_SET( B, RC_SERVO_PIN, 0UL );
	
	
	//GPIOB -> PUPDR &= ~ ( 0x3UL << (15*2)); // No pull for PB15
		// now can also use...
	GPIO_PUPDR_SET( B, RC_SERVO_PIN, 0UL );
	
	
	
	
	// Configure Timer 15
	
	// 1. Turn o Timer 15
		RCC -> APB2ENR |= RCC_APB2ENR_TIM15EN;
	
	// 2. Program Timer 15 prescaler to count in microseconds
		TIM15 -> PSC = SystemCoreClock / (1000000UL) - 1;
		//You need -1 to allow the timer start sequence (mandatory)
	
	// 3. Set TIM15 to upcounting mode (not mandatory, because upcounting mode is the default mode for F303 timers)
		// CLEAR_BITS(TIM15 -> CR1, TIM_CR1_DIR);
	
	// 4. Set the TIM15 reload value to 20000 us period (20000 - 1 because it's repeating)
		TIM15 -> ARR = 20000UL - 1;
	
	// 5. Enable TIM15 ARR preload
		SET_BITS( TIM15 -> CR1, TIM_CR1_ARPE );
	
	// 6. Set TIM15 main output enabled
		SET_BITS( TIM15 -> BDTR, TIM_BDTR_MOE );
	
	
	// Configure Channel 2 of TIM15 for PWM output compare mode
	
	// 1. Select PWM mode 1 for TIM15 channel 2
		FORCE_BITS( TIM15 -> CCMR1, TIM_CCMR1_OC2M, (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2) );
	
	// 2. Enable output compare preload on channel 2 (i.e. update counter register only on timer enabled (UE) )
		SET_BITS( TIM15 -> CCMR1, TIM_CCMR1_OC2PE );
	
	// 3. Enable the output channel (CH2)
		SET_BITS( TIM15 -> CCER, TIM_CCER_CC2E );
	
	// 4. Make CH2 active HI (standard polarity)
		CLEAR_BITS( TIM15 -> CCER, TIM_CCER_CC2P );
	
	// 5. Set the CH2 initial PWM ON-time to 0 by clearing CCR2, so that PWM will not be outputted until the first 20ms elapsed
		TIM15 -> CCR2 = 0;
	
	
	// Set TIM15 running, PWM signal out
	
	// 1. Force an update event to preload all the registers
		SET_BITS( TIM15 -> EGR, TIM_EGR_UG );
	
	// 2. Enable TIM15 to start counting
		SET_BITS( TIM15 -> CR1, TIM_CR1_CEN );
	
}


uint16_t RCServo_SetAngle( int16_t angle )
{

		uint16_t pulseWidth = CENTREPERIOD + (angle * 10);
	
		if(pulseWidth >= PW_MAX)
		{
			pulseWidth = PW_MAX;
		}
		
		if(pulseWidth <= PW_MIN)
		{
			pulseWidth = PW_MIN;
		}
		
		TIM15 -> CCR2 = pulseWidth;
		
		return (pulseWidth);
	
}
