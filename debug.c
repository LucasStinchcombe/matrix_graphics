#include "debug.h"
#include "uart.h"
#include <avr/io.h>

#define MYFOSC 16000000UL
#define BAUD 9600
#define MYUBRR MYFOSC / 16 / BAUD - 1

static int is_init = 0;

void debug_init()
{
    if (!is_init)
    {
        UART_init(MYUBRR);
        LOG("Debugging initialized.\n");
        is_init = 1;
    }
}

int put_char(char data, FILE *stream)
{
    // add carriage return
    if (data == '\n')
    {
        UART_transmit('\r');
    }
    UART_transmit(data);
    return 0;
}

FILE log_stream = FDEV_SETUP_STREAM(put_char, NULL, _FDEV_SETUP_WRITE);
