/*
*
*   uart.h
*
*   Used to set up the UART
*   uses UART1 at 115200
*
*
*   @author Dane Larson
*   @date 07/18/2016
*   Phillip Jones updated 9/2019, removed WiFi.h
*/

#ifndef UART_H_
#define UART_H_

#include "Timer.h"
#include <inc/tm4c123gh6pm.h>

void uart_init(void);

void uart_sendChar(char data);

char uart_receive(void);

// Initialize the UART to communciate between CyBot and PuTTy
void cyBot_uart_init(void);

// Send a byte over the UART from CyBot and PuTTy (Buad Rate 115200, No Parity, No Flow Control)
void cyBot_sendByte(char data);

// Cybot WAITs to recive a byte from PuTTy (Buad Rate 115200, No Parity, No Flow Control).
// In other words, this is a blocking fucntion.
int cyBot_getByte(void);

void uart_sendStr(const char *data);

char uart_byte_to_recive(void);

void uart_interrupt_init(void);

void uart1_Handler(void);


#endif /* UART_H_ */
