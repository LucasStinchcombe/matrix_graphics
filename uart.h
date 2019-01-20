#ifndef MATRIX_GRAPHICS_UART_H
#define MATRIX_GRAPHICS_UART_H

#include <avr/io.h>

void UART_init(unsigned int ubrr);
void UART_transmit(unsigned char data);
#endif
