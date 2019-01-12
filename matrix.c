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

uint16_t matrix[MATRIX_SIZE] = {
    0b1000001010000010,
    0b1100010111000101,
    0b1110101111101011,
    0b1111011111110111,
    0b1110111111101111,
    0b1101011111011111,
    0b1011011110100011,
    0b0111011101101011,
    0b1000001010000010,
    0b1100010111000101,
    0b1110101011101011,
    0b1111011111110111,
    0b1110111011111111,
    0b1101111011111111,
    0b1011111111111111,
    0b0111111101111111,
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
    int base_row;
    int aux_row;
    for(int i = 0; i != QUADRANT_SIZE; ++i)
    {
        base_row = QUADRANT_SIZE - i - 1;
        aux_row = MATRIX_SIZE - i - 1;

        send_code((i+1) << 8
                    | BYTE_BIT_SWAP(matrix[aux_row] >> QUADRANT_SIZE));
        send_code((i+1) << 8
                    | BYTE_BIT_SWAP(matrix[aux_row]));
        send_code((i+1) << 8
                    | BYTE_BIT_SWAP(matrix[base_row] >> QUADRANT_SIZE));
        send_code((i+1) << 8
                    | BYTE_BIT_SWAP(matrix[base_row]));
        SPI_slave_select();
    }
}
