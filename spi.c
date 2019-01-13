#include "spi.h"

#include <avr/io.h>
#include <util/delay.h>

#define MYFOSC 16000000UL
#define DDR_SPI DDRB
#define DD_SCK DDB5
#define DD_MOSI DDB3
#define DD_SS DDB2
#define PORT_SS PORTB2

void SPI_init()
{
    // enable MOSI, CLK, SS for output
    DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);

    // set SS to low
    PORTB &= ~(1 << PORT_SS);

    // enable SPI, set as master, clock rate to fosc/16, LSB first
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);

    // set polarity and phase to sample on leading rising edge
    SPCR &= ~((1 << CPOL) | (1 << CPHA));

    // disable double speed
    SPSR &= ~(1 << SPI2X);
}

static void SPI_transmit(unsigned char data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)))
        ;
}

void SPI_slave_select()
{
    // set SS to high for 1us and back to low
    PORTB |= (1 << PORT_SS);
    _delay_us(1);
    PORTB &= ~(1 << PORT_SS);
}

void send_code(uint16_t code)
{
    SPI_transmit(code >> 8);
    SPI_transmit(code & 255);
}
