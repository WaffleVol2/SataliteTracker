//Blaise Swan 
//keypad implementations 
#include "stm32f303xe.h"
#include "keypad.h"
#include "scottMacro.h"
#define ROW0_PIN 0
#define ROW1_PIN 1
#define ROW2_PIN 2
#define ROW3_PIN 3
#define COL0_PIN 4
#define COL1_PIN 5
#define COL2_PIN 6
#define COL3_PIN 7
#define NUM_ROWS 4
#define NUM_COLS 4
// Define GPIO port registers
#define ROW_PORT A
#define COL_PORT B

void matrix_init(void) {
  // set row pins to output and set them high
	int i;
  for (i = 0; i < NUM_ROWS; i++) {
    GPIO_MODER_SET(ROW_PORT, i, GPIO_MODE_OUT);
    GPIO_OTYPER_SET(ROW_PORT, i, GPIO_OTYPE_PP);
    GPIO_PUPDR_SET(ROW_PORT, i, GPIO_PUPD_NO);
   // SET_GPIO_SPEED(ROW_PORT, i, GPIO_SPEED_FREQ_HIGH);
   // SET_GPIO_STATE(ROW_PORT, i, GPIO_PIN_SET);
  }

  // set column pins to input with pull-up
	
  for (i = 0; i < NUM_COLS; i++) {
    GPIO_MODER_SET(COL_PORT, i, GPIO_MODE_IN);
    GPIO_OTYPER_SET(COL_PORT, i, GPIO_OTYPE_PP);
    GPIO_PUPDR_SET(COL_PORT, i, GPIO_PUPD_PU);
   
  }
}


uint8_t MatrixScan(void)
{
    uint8_t row, col, row_pin, col_pin, NO_KEY_PRESSED;
		NO_KEY_PRESSED = 0;

    // set row output pins to 0
    for (row = 0; row < NUM_ROWS; row++) {
        row_pin = 1 << row;
        //GPIO_RESET_PIN(ROW_PORT, row); // set row pin low
			GPIOA->BSRR = (1 << (row + 16));

    }

    // scan columns
    for (col = 0; col < NUM_COLS; col++) {
        col_pin = 1 << col;

        // set current column as input
       // GPIO_SET_MODE_INPUT(COL_PORT, COL_PINS[col]);
       // GPIO_SET_PULL_UP(COL_PORT, COL_PINS[col]);
			
    
    // Set current column as input
    GPIOB->MODER &= ~(GPIO_MODER_MODER0 << (2 * col)); // Set as input
    GPIOB->PUPDR |= GPIO_PUPDR_PUPDR0_1 << (2 * col); // Set pull-up

        // check if any button in current column is pressed
        for (row = 0; row < NUM_ROWS; row++) {
            row_pin = 1 << row;

            // set current row as output and high
           // GPIO_SET_MODE_OUTPUT(ROW_PORT, row);
            //GPIO_SET_PIN_HIGH(ROW_PORT, row);
					
    // set current row as output and high
    GPIOA->MODER &= ~(3UL << (2 * row));   // set mode to output
    GPIOA->MODER |= 1UL << (2 * row);      // set mode to output
    GPIOA->ODR |= row_pin;                 // set pin high

    if ((GPIOB->IDR & col) == 0) {
						// debounce button press
						debounce();
		
    // check if button still pressed
						if ((GPIOB->IDR & col) == 0) {
        // button is pressed, return corresponding key value
        GPIOA->BSRR = row << 16; // set row pin low again
        return keys[row][col];
    }
}

            // set current row as output and low
            GPIO_SET_PIN_LOW(ROW_PORT, ROW_PINS[row]);
        }

        // set current column as output and high
        GPIO_SET_MODE_OUTPUT(COL_PORT, COL_PINS[col]);
        GPIO_SET_PIN_HIGH(COL_PORT, COL_PINS[col]);
    }

    // no button pressed
    return NO_KEY_PRESSED;
}


