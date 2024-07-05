////////////////
// LED Module
////////////////

#include "LED.h"
#include "utility.h"

void LED_init(void)
{
	//1. Enable Clock
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	
	//2. GPIO Mode Register
	GPIOA -> MODER &= ~(3UL << (2*5)); 	// Clear bits 10 and 11 for pin 5
	GPIOA -> MODER |= 1UL << (2*5); 		// Set bit 10, set Pin 5 as output
	
	//3. GPIO Output Type Register
	GPIOA -> OTYPER &= ~(1UL << 5); 		// Clear bit 5 for push-pull mode
	
	//4. GPIO Output Data Register
	GPIOA -> ODR |= 1UL << 5; 					// Write logic 1 to pin 5
	//GPIOA -> ODR &= ~(1UL << 5); 					// Write logic 0 to pin 5
}

	
void Toggle_LED(void)
{
	GPIOA -> ODR ^= (1UL << 5); // XOR to toggle bit!
}

void LED_OFF(void)
{
	GPIOA -> ODR &= ~(1UL << 5); 					// Write logic 0 to pin 5
}

void LED_ON(void)
{
	GPIOA -> ODR |= 1UL << 5; 					// Write logic 1 to pin 5
}
