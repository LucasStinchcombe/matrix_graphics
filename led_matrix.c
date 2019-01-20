#include "led_matrix.h"
#include "spi.h"
#include <util/delay.h>

#define QUADRANT_SIZE 8
#define PULSE_LEVELS 4

#define BIT(x, i) ((x & (1 << i)) >> i)
#define BYTE_BIT_SWAP(x)                                                       \
    (BIT(x, 0) << 7 | BIT(x, 1) << 6 | BIT(x, 2) << 5 | BIT(x, 3) << 4 |       \
     BIT(x, 4) << 3 | BIT(x, 5) << 2 | BIT(x, 6) << 1 | BIT(x, 7) << 0)

void matrix_init() { SPI_init(); }

void send_matrix()
{
    int base_row;
    int aux_row;
    for (int i = 0; i != QUADRANT_SIZE; ++i)
    {
        base_row = QUADRANT_SIZE - i - 1;
        aux_row = MATRIX_SIZE - i - 1;

        send_code((i + 1) << 8 |
                  BYTE_BIT_SWAP(matrix[aux_row] >> QUADRANT_SIZE));
        send_code((i + 1) << 8 | BYTE_BIT_SWAP(matrix[aux_row]));
        send_code((i + 1) << 8 |
                  BYTE_BIT_SWAP(matrix[base_row] >> QUADRANT_SIZE));
        send_code((i + 1) << 8 | BYTE_BIT_SWAP(matrix[base_row]));
        SPI_slave_select();
    }
}

void send_matrix_code(uint16_t code)
{
    for (int i = 0; i != 4; ++i)
    {
        send_code(code);
    }
    SPI_slave_select();
}

void pulse_matrix()
{
    for (uint8_t i = 0; i != PULSE_LEVELS; ++i)
    {
        send_matrix_code(0x0A00 | i);
        _delay_ms(25);
    }

    for (uint8_t i = 0; i != PULSE_LEVELS; ++i)
    {
        send_matrix_code(0x0A00 | PULSE_LEVELS - i);
        _delay_ms(25);
    }
}
