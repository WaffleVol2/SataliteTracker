// utility module

#include "utility.h"

void Delay_Arbitrary(void)  // this is only for blocking for loop delay.
{
	for(int i = 0; i < DELAY_CONSTANT; i++);
}


void Delay_ms (uint32_t msec)
{
	SysTick -> CTRL = 0;  // this will set ENABLE = 0, TINT = 0, CLKSRC = AHB/8, and clear the COUNTFLAG
	SysTick -> LOAD = ((SystemCoreClock / 8) / 1000UL) * msec;  // set the reload value
	SysTick -> VAL = 0;		// Reset the SysTick timer counter value
	
	SysTick -> CTRL |= SysTick_CTRL_ENABLE_Msk;  // Enable SysTick
	
	while( (SysTick -> CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0 );  // Wait until the countdown is done
	
	SysTick -> CTRL = 0;
}
