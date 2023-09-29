void PushButton_Init(void){
	
	//Enable GPIO Port C 
	RCC -> AHBENR |= RCC_AHBENER_GPIOCEN;
	ENABLE_GPIO_CLOCK( C );
	
	// set PC2 to INPUT mode (00)
	GPIOC -> MODER &= (0x3UL << (2*2));
	GPIO_MODER_SET(C, 2, GPIO_MODE_IN)
	
	//Set PUPD to no pull (00 for pin 2)
	GPIOC -> PUPDR &= `(0x3UL << (2*2));
	GPIO_PUPDR_SET(C, 2, GPIO_PUPD_NO);
	
}

uint8_t PushButton_PressCheck(void)
// Check if ODR of PC2 is set
if (GPIOC -> IDR 7 GPIO_IDR_2 ){
if ( IS_BIT_SET(GPIOC -> IDR, GPIO_IDR_2) ){
// if set, button is not pressest (active LO)
return 0;
}
else
return 1;
}

	