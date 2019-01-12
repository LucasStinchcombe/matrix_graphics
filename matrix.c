#include "matrix.h"
#include "spi.h"

#define MATRIX_SIZE 8

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
    for(int i = 0; i != MATRIX_SIZE; ++i)
    {
        for (int j = 0; j != 4; ++j)
        {
            send_code((i+1) << 8
                    | BYTE_BIT_SWAP(matrix[MATRIX_SIZE - i - 1]));
        }
        SPI_slave_select();
    }
}
