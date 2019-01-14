#include "debug.h"
#include "uart.h"
#include <avr/io.h>

#define MYFOSC 16000000UL
#define BAUD 9600
#define MYUBRR MYFOSC / 16 / BAUD - 1

void debug_init() { UART_init(MYUBRR); }

int put_char(char data, FILE *stream)
{
    if (data == '\n')
    {
        UART_transmit('\r');
    }
    UART_transmit(data);
    return 0;
}

FILE log_stream = FDEV_SETUP_STREAM(put_char, NULL, _FDEV_SETUP_WRITE);
