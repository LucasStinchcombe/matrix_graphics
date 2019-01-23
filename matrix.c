#include "matrix.h"
#include "debug.h"

#include <float.h>
#include <math.h>

#define RASTERIZATION_THRESHOLD 0.01
#define QUADRANT_SIZE 8
#define PULSE_LEVELS 4

#define COORD(x) (MATRIX_SIZE - x - 1)

uint16_t matrix[MATRIX_SIZE];

// expects that p2.x >= p1.x && p2.y >= p1.y
static int pop_endpoint(vector2d_t *vec, point2d_t *point)
{
    if (vec->p1.x == vec->p2.x && vec->p1.y == vec->p2.y)
    {
        return 0;
    }

    *point = vec->p1;
    float m = (vec->p2.y - vec->p1.y) / (vec->p2.x - vec->p1.x);
    float b = point->y - (m * point->x);

    TRACE_LOG("m = %f; b = %f;\n", m, b);

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
        point2d_t x_candidate = {.x = floor(point->x + 1),
                                .y = lin_func(m, b, floor(point->x) + 1)};

        point2d_t y_candidate = {
            .x = lin_func(1.0 / m, -b / m, floor(point->y) + 1),
            .y = floor(point->y + 1)};

        TRACE_LOG("x-candidate (%f,%f)\n", x_candidate.x, x_candidate.y);
        TRACE_LOG("y-candidate (%f,%f)\n", y_candidate.x, y_candidate.y);

        // get next point that intersects with grid with threshold
        if (x_candidate.x < y_candidate.x - RASTERIZATION_THRESHOLD &&
            x_candidate.y < y_candidate.y - RASTERIZATION_THRESHOLD)
        {
            vec->p1 = x_candidate;
        }
        else
        {
            vec->p1 = y_candidate;
        }
    }
    DEBUG_LOG("chosen (%f,%f)\n", vec->p1.x, vec->p1.y);

    if ((vec->p1.x > vec->p2.x) || (vec->p1.y > vec->p2.y) || isnan(m))
    {
        vec->p1 = vec->p2;
    }
    return 1;
}

void fix_bounds(point2d_t *point)
{
    point->x = fmax(0.0, point->x);
    point->x = fmin(16.0, point->x);
    point->y = fmax(0.0, point->y);
    point->y = fmin(16.0, point->y);
}

void matrix_draw(vector2d_t vec)
{
    INFO_LOG("Rasterizing vector ((%f,%f), (%f,%f))\n", vec.p1.x, vec.p1.y,
             vec.p2.x, vec.p2.y);

    // TODO assert that in range
    fix_bounds(&vec.p1);
    fix_bounds(&vec.p2);

    int sign_x = vec.p2.x < vec.p1.x ? -1 : 1;
    int sign_y = vec.p2.y < vec.p1.y ? -1 : 1;

    TRACE_LOG("Multiplying by scalars (%d,%d)\n", sign_x, sign_y);

    // scale by 16 and transform by sign
    vec.p1.x *= 16 * sign_x;
    vec.p1.y *= 16 * sign_y;
    vec.p2.x *= 16 * sign_x;
    vec.p2.y *= 16 * sign_y;

    INFO_LOG("Running algorithm on ((%f,%f), (%f,%f))\n", vec.p1.x, vec.p1.y,
             vec.p2.x, vec.p2.y);

    point2d_t point;
    while (pop_endpoint(&vec, &point))
    {
        TRACE_LOG("popped endpoint (%f,%f)\n", point.x, point.y);
        TRACE_LOG("remaining vector ((%f,%f), (%f,%f))\n", vec.p1.x, vec.p1.y,
                  vec.p2.x, vec.p2.y);
        int x_coord = (sign_x > 0 ? (int)(sign_x * point.x)
                                  : (int)(ceil(sign_x * point.x - 1)));

        int y_coord = (sign_y > 0 ? (int)(sign_y * point.y)
                                  : (int)(ceil(sign_y * point.y - 1)));

        if (0 <= y_coord && y_coord < 16 && 0 <= x_coord && x_coord < 16)
        {
            DEBUG_LOG("matrix coordinates (%d,%d)\n", x_coord, y_coord);
            matrix[COORD(y_coord)] |= 1 << COORD(x_coord);
        }
    }
}

void matrix_basis(vector2d_t *vec)
{
    vec->p1.x += 0.5;
    vec->p1.y += 0.5;
    vec->p2.x += 0.5;
    vec->p2.y += 0.5;
}

void matrix_clear()
{
    for(int i = 0; i != MATRIX_SIZE; ++i)
    {
        matrix[i] = 0;
    }
}
