#include <avr/io.h>
#include <util/delay.h>

#include "spi.h"
#include "conway.h"

void pulse()
{
    for (uint8_t i = 0; i != 16; ++i)
    {
        send_code(0x0A00 | i);
        send_code(0x0A00 | i);
        send_code(0x0A00 | i);
        send_code(0x0A00 | i);
        SPI_slave_select();
        _delay_ms(25);
    }


    for (uint8_t i = 0; i != 16; ++i)
    {
        send_code(0x0A00 | 15 - i);
        send_code(0x0A00 | 15 - i);
        send_code(0x0A00 | 15 - i);
        send_code(0x0A00 | 15 - i);
        SPI_slave_select();
        _delay_ms(25);
    }

}

int main()
{
    SPI_init();
    _delay_ms(100);

    // disable test mode
    send_code(0x0F00);
    send_code(0x0F00);
    send_code(0x0F00);
    send_code(0x0F00);
    SPI_slave_select();

    // disable decode
    send_code(0x0900);
    send_code(0x0900);
    send_code(0x0900);
    send_code(0x0900);
    SPI_slave_select();

    // scan all digits
    send_code(0x0B07);
    send_code(0x0B07);
    send_code(0x0B07);
    send_code(0x0B07);
    SPI_slave_select();

    // set min intensity
    send_code(0x0A01);
    send_code(0x0A01);
    send_code(0x0A01);
    send_code(0x0A01);
    SPI_slave_select();

    // disable shutdown mode
    send_code(0x0C01);
    send_code(0x0C01);
    send_code(0x0C01);
    send_code(0x0C01);
    SPI_slave_select();

    while(1)
    {
        send_matrix();
    }
}
