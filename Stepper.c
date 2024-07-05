// Stepper Motor Control Signals via PC0 - PC3

#include "Stepper.h"
#include "utility.h"

static uint8_t currentStepIndex = 0;

static const uint16_t stepPatternTable[8] = 
{
	0x8,
	0xA,
	0x2,
	0x6,
	0x4,
	0x5,
	0x1,
	0x9
};

void Stepper_Init(void)
{

		// Enable GPIO Port C clock
		RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
	
		// Set PC0 to have Output Mode, No Pull, and Push-Pull (default)
		GPIOC -> MODER &= ~(0x3UL << (2*0)); 	// Clear both bits
		GPIOC -> MODER |=  (0x1UL << (2*0)); 	// Set 01 as output
	
		GPIOC -> PUPDR &= ~(0x3UL << (2*0)); // No pull

		GPIOC -> OTYPER &= ~(0x1UL << 0); // push-pull
			
		// Do the same for PC1, PC2, and PC3
		GPIOC -> MODER &= ~(0x3UL << (2*1)); 	// Clear both bits
		GPIOC -> MODER |=  (0x1UL << (2*1)); 	// Set 01 as output
	
		GPIOC -> PUPDR &= ~(0x3UL << (2*1)); // No pull

		GPIOC -> OTYPER &= ~(0x1UL << 1); // push-pull
	
	
		GPIOC -> MODER &= ~(0x3UL << (2*2)); 	// Clear both bits
		GPIOC -> MODER |=  (0x1UL << (2*2)); 	// Set 01 as output
	
		GPIOC -> PUPDR &= ~(0x3UL << (2*2)); // No pull

		GPIOC -> OTYPER &= ~(0x1UL << 2); // push-pull


		GPIOC -> MODER &= ~(0x3UL << (2*3)); 	// Clear both bits
		GPIOC -> MODER |=  (0x1UL << (2*3)); 	// Set 01 as output
	
		GPIOC -> PUPDR &= ~(0x3UL << (2*3)); // No pull

		GPIOC -> OTYPER &= ~(0x1UL << 3); // push-pull
}

void Stepper_Step(int8_t stepType)
{
	//currentStepIndex = (currentStepIndex + stepType) % 8;  	// so to wrap around the array
																													// also you should try to 3-bit mask method
	// the CPU performance impact may not be as much.  both MOD and bitwise mask & are done by ALU
	// However, the general rule of thumb is that ARM cores would prefer bitmask &
	// Performance optimization may be done through the compiler, but you should be aware of the underlying
	//  performance impact.
	
	// Alternative Version (mask version)
	currentStepIndex += stepType;
	currentStepIndex &= STEP_INDEX_MASK;
	
	//UARTprintf("Stepping: %d, Type: %d, Pattern: %x\n", currentStepIndex, stepType, stepPatternTable[currentStepIndex]);
	
	FORCE_BITS(GPIOC->ODR, 0x000F, stepPatternTable[currentStepIndex]);
	//GPIOC -> ODR = stepPatternTable[currentStepIndex];
	
	
}
