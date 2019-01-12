#include "matrix.h"
#include "spi.h"

#define QUADRANT_SIZE 8
#define BIT(x, i) ((x & (1 << i)) >> i)
#define BYTE_BIT_SWAP(x) (BIT(x, 0) << 7 \
                         |BIT(x, 1) << 6 \
                         |BIT(x, 2) << 5 \
                         |BIT(x, 3) << 4 \
                         |BIT(x, 4) << 3 \
                         |BIT(x, 5) << 2 \
                         |BIT(x, 6) << 1 \
                         |BIT(x, 7) << 0)

uint8_t matrix[MATRIX_SIZE] = {
    0b10000010,
    0b11000101,
    0b11101011,
    0b11110111,
    0b11101111,
    0b11011111,
    0b10111111,
    0b01111111,
};

/*
uint8_t matrix[MATRIX_SIZE] = {
    0b00010010,
    0b01101010,
    0b00010110,
    0b01010100,
    0b00010110,
    0b10100011,
    0b01010101,
    0b10010110,
};
*/

void matrix_init()
{
    SPI_init();
}

void send_matrix()
{
    for(int i = 0; i != QUADRANT_SIZE; ++i)
    {
        for (int j = 0; j != 4; ++j)
        {
            send_code((i+1) << 8
                    | BYTE_BIT_SWAP(matrix[MATRIX_SIZE - i - 1]));
        }
        SPI_slave_select();
    }
}
