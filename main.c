#include <avr/io.h>
#include <util/delay.h>

#include "spi.h"
#include "matrix.h"
#include "conway.h"

int main()
{
    SPI_init();
    _delay_ms(100);

    // disable test mode
    send_matrix_code(0x0F00);

    // disable decode
    send_matrix_code(0x0900);

    // scan all digits
    send_matrix_code(0x0B07);

    // set min intensity
    send_matrix_code(0x0A01);

    // disable shutdown mode
    send_matrix_code(0x0C01);

    while(1)
    {
        send_matrix();
        next_iter();

        _delay_ms(100);
    }
}
