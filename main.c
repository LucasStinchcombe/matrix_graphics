#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

// TODO cleanup includes for all sources
#include "conway.h"
#include "debug.h"
#include "math.h"
#include "matrix.h"
#include "spi.h"
#include "vector.h"

int main()
{
    LOG_INIT();

    matrix_init();

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

    // vector_2d vec = {{1.0/16, 2.0/16}, {14.0/16, 15.0/16}};
    vector_2d vec = {{0.0, 0.0}, {1.0, 0.0}};
    matrix_draw(vec);
    vector_2d vec2 = {{0.0, 0.0}, {0.5, 1.0}};
    matrix_draw(vec2);
    vector_2d vec3 = {{0.5, 1.0}, {1.0, 0.0}};
    matrix_draw(vec3);

    while (1)
    {
        send_matrix();
        // next_iter();
        _delay_ms(500);
    }
}
