#include <avr/io.h>
#include <util/delay.h>

#include "spi.h"
#include "conway.h"

void send_matrix()
{
    for(int i = 0; i != MATRIX_SIZE; ++i)
    {
        send_code((i+1) << 8 | matrix[i]);
    }
}

void pulse()
{
    for (uint8_t i = 0; i != 16; ++i)
    {
        send_code(0x0A00 | i); 
        _delay_ms(25);
    }

    _delay_ms(500);

    for (uint8_t i = 0; i != 16; ++i)
    {
        send_code(0x0A00 | 15 - i);
        _delay_ms(25);
    }

}

int main()
{
    SPI_init();
    _delay_ms(100);

    // disable decode
    send_code(0x0900);

    // scan all digits
    send_code(0x0B07);

    // set min intensity
    send_code(0x0A00); 

    // disable shutdown mode
    send_code(0x0C01);


    while(1)
    {
        send_matrix();
        //pulse();
        //next_iter();
    }
}
