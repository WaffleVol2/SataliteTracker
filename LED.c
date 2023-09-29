/*

/////// LED Demo 
*/

#include "LED.h"
void LED_INIT(void){ 
	//initialize
	
	// 1 turn on the AHB so GPIOs are ON
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	// 2. GPIO Mode Register -> set to output
	GPIOA->MODER &= ~(3UL << (2*5)); //reset the two bits for PA5
	GPIOA->MODER |= (1UL << (2*5));// set the two bits to OUTPUT (01) for PA5
	// 3. Set GPIO Output type to push pull (clear logic 0)
	GPIOA->OTYPER &= ~(1UL << (1*5));
	// 4 (optional) set GPIO pull-up / pull down register to default (no pull)
	GPIOA->PUPDR &= ~(3UL << (2*5));
	// 5 write logic 1 to GPIOA ODR bit 5 (PA5 to Controlling LED)
	GPIOA->ODR |= (1UL << (1*5)); //TURN LED ON
	//Program Loop
}
void TOGGLE(void){
	GPIOA->ODR ^= (1UL << (1*5)); //TURN LED ON
}
