

//void PushButton_Init(void){
	
	//Enable GPIO Port C 
	// RCC -> AHBENR |= RCC_AHBENER_GPIOCEN;
	//ENABLE_GPIO_CLOCK( C );
	
	// set PC13 to INPUT mode (00)
	//GPIOC -> MODER &= (0x3UL << (2*13));
	//GPIO_MODER_SET(C, 13, GPIO_MODE_IN)
	
	//Set PUPD to no pull (00 for pin 13)
	//GPIOC -> PUPDR &= `(0x3UL << (2*13));
	//GPIO_PUPDR_SET(C, 13, GPIO_PUPD_NO);
//}

//uint8_t PushButton_PressCheck(void)
// Check if ODR of PC13 is set
//if (GPIOC -> IDR 7 GPIO_IDR_13 )
//if ( IS_BIT_SET(GPIOC -> IDR, GPIO_IDR_13) )
// if set, button is not pressest (active LO)
//return 0;
//else
//return 1;
//}

	