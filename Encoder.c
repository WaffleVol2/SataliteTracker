// Motor Encoder Module Source File

#include "Encoder.h"

void Encoder_Init(void)
{
	ENABLE_GPIO_CLOCK( ENCODER_PORT );
	
	// PA0 for Input Capture on Left Wheel
	GPIO_MODER_SET( ENCODER_PORT, LEFT_ENCODER_PIN, GPIO_MODE_AF );
	FORCE_BITS( GPIOA -> AFR[0], GPIO_AFRL_AFRL0_Msk, 0x1UL << GPIO_AFRL_AFRL0_Pos );
	GPIO_PUPDR_SET( ENCODER_PORT, LEFT_ENCODER_PIN, GPIO_PUPD_PU );
	
	// PA1 for Input Capture on Right Wheel
	GPIO_MODER_SET( ENCODER_PORT, RIGHT_ENCODER_PIN, GPIO_MODE_AF );
	FORCE_BITS( GPIOA -> AFR[0], GPIO_AFRL_AFRL1_Msk, 0x1UL << GPIO_AFRL_AFRL1_Pos );
	GPIO_PUPDR_SET( ENCODER_PORT, RIGHT_ENCODER_PIN, GPIO_PUPD_PU );
	
	
	// Configure TIM2 for Both CH1 and CH2 inputs
	
	// Enable TIM2 on APB1
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	// Set Prescaler to 1us
	ENCODER_TIMER -> PSC = SystemCoreClock / (1000000UL) - 1;  
	
	// Set counting direction to upcounting
	CLEAR_BITS( ENCODER_TIMER -> CR1, TIM_CR1_DIR );  //set to zero for upcounting
	
	
	
	// Configure TIM2 CH1 for input capture on Left Encoder
	
	// Select input capture mode for CH1 (normal mode  0%01)
	FORCE_BITS(ENCODER_TIMER -> CCMR1, TIM_CCMR1_CC1S, TIM_CCMR1_CC1S_0);  // leave CC1S_1 zero / untouched
	
	// ENABLE_GPIO_CLOCK input capture for CH1
	SET_BITS(ENCODER_TIMER -> CCER, TIM_CCER_CC1E);
	
	// Detect rising edges (by clearing both input capture mode bits)
	CLEAR_BITS(ENCODER_TIMER -> CCER, TIM_CCER_CC1P);
	CLEAR_BITS(ENCODER_TIMER -> CCER, TIM_CCER_CC1NP);
	
	// Clear CCR1 of any garbage values
	ENCODER_TIMER -> LEFT_ENCODER_CH = 0;
	
	
	
	// Configure TIM2 CH2 for input capture on Right Encoder
	
	// Select input capture mode for CH2 (normal mode  0%01)
	FORCE_BITS(ENCODER_TIMER -> CCMR1, TIM_CCMR1_CC2S, TIM_CCMR1_CC2S_0);  // leave CC1S_1 zero / untouched
	
	// ENABLE_GPIO_CLOCK input capture for CH2
	SET_BITS(ENCODER_TIMER -> CCER, TIM_CCER_CC2E);
	
	// Detect rising edges (by clearing both input capture mode bits)
	CLEAR_BITS(ENCODER_TIMER -> CCER, TIM_CCER_CC2P);
	CLEAR_BITS(ENCODER_TIMER -> CCER, TIM_CCER_CC2NP);
	
	// Clear CCR2 of any garbage values
	ENCODER_TIMER -> RIGHT_ENCODER_CH = 0;
	
	
	
	
	// Configure TIM2 to generate interrupts and configure NVIC to respond
	
	// Enable Encoder channels to trigger IRQ
	SET_BITS( ENCODER_TIMER -> DIER, TIM_DIER_CC1IE );
	SET_BITS( ENCODER_TIMER -> DIER, TIM_DIER_CC2IE );
	
	NVIC_SetPriority( ENCODER_TIMER_INT, 3 );  // can bey any priority.  No real reason.
	NVIC_EnableIRQ( ENCODER_TIMER_INT );
	
	
	// Start TIM2 CH1 and CH2 Input Captures
	
	// 1. Force an update event to preload all the registers
		SET_BITS( ENCODER_TIMER -> EGR, TIM_EGR_UG );
	
	// 2. Enable TIM15 to start counting
		SET_BITS( ENCODER_TIMER -> CR1, TIM_CR1_CEN );
	
}



uint32_t leftEncoderPeriod;
uint32_t rightEncoderPeriod;

static uint32_t lastLeftCHVal = 0;
static uint32_t lastRightCHVal = 0;


void TIM2_IRQHandler( void )
{

	uint32_t currentLeftCHVal;
	uint32_t currentRightCHVal;
	
	// If CH1 fires the IRQ, Calculate Left Encoder Period.  
	// Unsigned INT automatically deals with the overflow wraparound nicely
	if( ENCODER_TIMER -> SR & TIM_SR_CC1IF )
	{
		currentLeftCHVal = ENCODER_TIMER -> LEFT_ENCODER_CH;
		leftEncoderPeriod = currentLeftCHVal - lastLeftCHVal;
		lastLeftCHVal = currentLeftCHVal;
	}
	
	// If CH2 fires the IRQ, Calculate Right Encoder Period.  
	if( ENCODER_TIMER -> SR & TIM_SR_CC2IF )
	{
		currentRightCHVal = ENCODER_TIMER -> RIGHT_ENCODER_CH;
		rightEncoderPeriod = currentRightCHVal - lastRightCHVal;
		lastRightCHVal = currentRightCHVal;
	}
	
}


// Helper Function for Debugging
uint32_t getEncoderCHValue( uint8_t enc )
{
	uint32_t currentEncoderValue;
	
	switch(enc)
	{
		case LEFT_ENC:
			while( !(ENCODER_TIMER -> SR & TIM_SR_CC1IF) );
			currentEncoderValue = ENCODER_TIMER -> LEFT_ENCODER_CH;
			break;
		
		case RIGHT_ENC:
			while( !(ENCODER_TIMER -> SR & TIM_SR_CC2IF) );
			currentEncoderValue = ENCODER_TIMER -> RIGHT_ENCODER_CH;
			break;
		
		default:
			currentEncoderValue = 0;
			break;
	
	}
	
	return (currentEncoderValue);
}

