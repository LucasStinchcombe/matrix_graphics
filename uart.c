#include <avr/io.h>

void UART_init(unsigned int ubrr)
{
    // set baud rate registers
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)ubrr;

    // disable double speed
    UCSR0A &= ~(1 << U2X0);

    // enable transmitter bit
    UCSR0B = (1 << TXEN0);

    // 8 bit data
    // asynchronous
    // no parity bit
    // one stop bit
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void UART_transmit(unsigned char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}
