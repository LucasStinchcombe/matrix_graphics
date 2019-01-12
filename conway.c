#include "conway.h"
#include "spi.h"

#define MATRIX_SIZE 8
#define BELOW_POS(pos) ((pos + (MATRIX_SIZE - 1)) % MATRIX_SIZE)
#define ABOVE_POS(pos) ((pos + 1 ) % MATRIX_SIZE)

uint8_t matrix[MATRIX_SIZE] = {
    0b10000010,
    0b11000101,
    0b11101011,
    0b11110111,
    0b11101111,
    0b11011011,
    0b10100001,
    0b01000000,
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

static uint8_t next[MATRIX_SIZE];

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


void next_iter()
{
    int i, j, count;

    for(i = 0; i != MATRIX_SIZE; ++i)
    {
        for (j = 0; j != MATRIX_SIZE; ++j)
        {
            count = 0;

            if (matrix[i] & 1 << BELOW_POS(j))
            {
                ++count;
            }
            if (matrix[i] & 1 << ABOVE_POS(j))
            {
                ++count;
            }
            if (matrix[BELOW_POS(i)] & 1 << j)
            {
                ++count;
            }
            if (matrix[ABOVE_POS(i)] & 1 << j)
            {
                ++count;
            }
            if (matrix[BELOW_POS(i)] & 1 << BELOW_POS(j))
            {
                ++count;
            }
            if (matrix[BELOW_POS(i)] & 1 << ABOVE_POS(j))
            {
                ++count;
            }
            if (matrix[ABOVE_POS(i)] & 1 << BELOW_POS(j))
            {
                ++count;
            }
            if (matrix[ABOVE_POS(i)] & 1 << ABOVE_POS(j))
            {
                ++count;
            }

            // if alive
            if(matrix[i] & 1 << j)
            {
                if(count < 2 || count > 3)
                {
                    next[i] &= ~(1 << j);
                }
                else
                {
                    next[i] |= 1 << j;
                }
            }
            else if(count == 3)
            {
                next[i] |= 1 << j;
            }
            else
            {
                next[i] &= ~(1 << j);
            }
        }
    }

    // copy new matrix
    for(i = 0; i != MATRIX_SIZE; ++i)
    {
        matrix[i] = next[i];
    }
}
