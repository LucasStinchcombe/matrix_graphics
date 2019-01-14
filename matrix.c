#include "matrix.h"
#include "debug.h"
#include "spi.h"

#include <util/delay.h>

#define QUADRANT_SIZE 8
#define BIT(x, i) ((x & (1 << i)) >> i)
#define BYTE_BIT_SWAP(x)                                                       \
    (BIT(x, 0) << 7 | BIT(x, 1) << 6 | BIT(x, 2) << 5 | BIT(x, 3) << 4 |       \
     BIT(x, 4) << 3 | BIT(x, 5) << 2 | BIT(x, 6) << 1 | BIT(x, 7) << 0)

#define COORD(x) (MATRIX_SIZE - x - 1)

#define PULSE_LEVELS 4

// clang-format off
/*
uint16_t matrix[MATRIX_SIZE] = {
    0b0000000000000000,
    0b0000000000000000,
    0b0010010000000000,
    0b0100000000000000,
    0b0100010000000000,
    0b0111100000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000010010,
    0b0000000000000001,
    0b0000000000010001,
    0b0000000000001111,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
};

uint16_t matrix[MATRIX_SIZE] = {
    0b0001001000010010,
    0b0110101001101010,
    0b0001011000010110,
    0b0101010001010100,
    0b0001011000010110,
    0b1010001110100011,
    0b0101010101010101,
    0b1001011010010110,
    0b0001001000010010,
    0b0110101001101010,
    0b0001011000010110,
    0b0101010001010100,
    0b0001011000010110,
    0b1010001110100011,
    0b0101010101010101,
    0b1001011010010110,
};
*/
// clang-format on

uint16_t matrix[MATRIX_SIZE];

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

// expects that p2.x >= p1.x && p2.y >= p1.y
static int pop_endpoint(vector_2d *vec, point_2d *point)
{
    *point = vec->p1;
    float m = (vec->p2.y - vec->p1.y) / (vec->p2.x - vec->p1.x);
    float b = point->y - (m * point->x);

    LOG("m = %f; b = %f;\n", m, b);

    if (m == 0.0)
    {
        vec->p1.x = floor(point->x) + 1;
        vec->p1.y = vec->p2.y;
    }
    else if (isinf(m))
    {
        vec->p1.x = vec->p2.x;
        vec->p1.y = floor(point->y) + 1;
    }
    else
    {
        point_2d x_candidate = {.x = floor(point->x + 1),
                                .y = lin_func(m, b, floor(point->x) + 1)};

        point_2d y_candidate = {
            .x = lin_func(1.0 / m, -b / m, floor(point->y) + 1),
            .y = floor(point->y + 1)};

        LOG("x-candidate (%f,%f)\n", x_candidate.x, x_candidate.y);
        LOG("y-candidate (%f,%f)\n", y_candidate.x, y_candidate.y);

        // get next point that intersects with grid
        vec->p1 = (x_candidate.x < y_candidate.x) ? x_candidate : y_candidate;
    }
    LOG("chosen (%f,%f)\n", vec->p1.x, vec->p1.y);

    return !(vec->p1.x > vec->p2.x) && !(vec->p1.y > vec->p2.y) && !isnan(m);
}

void matrix_draw(vector_2d vec)
{
    // TODO assert that in range
    int sign_x = vec.p2.x < vec.p1.x ? -1 : 1;
    int sign_y = vec.p2.y < vec.p1.y ? -1 : 1;

    LOG("(x,y) scalars: (%d,%d)\n", sign_x, sign_y);

    // scale by 16 and transform by sign
    vec.p1.x *= 16 * sign_x;
    vec.p1.y *= 16 * sign_y;
    vec.p2.x *= 16 * sign_x;
    vec.p2.y *= 16 * sign_y;

    point_2d point;
    while (pop_endpoint(&vec, &point))
    {
        LOG("endpoint (%f,%f)\n", point.x, point.y);
        int x_coord =
            (sign_x > 0 ? (int)point.x : (int)(ceil(sign_x * point.x - 1)));

        int y_coord =
            (sign_y > 0 ? (int)point.y : (int)(ceil(sign_y * point.y - 1)));

        LOG("matrix coords (%d,%d)\n", x_coord, y_coord);
        LOG("vec ((%f,%f), (%f,%f))\n", vec.p1.x, vec.p1.y, vec.p2.x, vec.p2.y);

        matrix[COORD(y_coord)] |= 1 << COORD(x_coord);
#ifdef DEBUG
        _delay_ms(1000);
#endif
    }
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
