///////////////////////
// UART Module Header
///////////////////////

#ifndef __STM3F303RE_UART_H
#define __STM3F303RE_UART_H

#include "stm32f303xe.h"

#define BAUD_RATE 9600
#define BufferSize 32
//uint8_t USART2_Buffer_Rx[BufferSize];
//volatile uint32_t Rx2_Counter = 0;
void UART2_Init(void);

void UARTputc(char myChar);
void UARTputs(char *myStr);
char UARTgetc(void);
char UARTgetcNB(void);

void UARTprintf( char *format, ... );
void USART2_IRQhandler(void);
void recieve(USART_TypeDef *USARTx, uint8_t *buffer, uint32_t *pCounter);

#endif
