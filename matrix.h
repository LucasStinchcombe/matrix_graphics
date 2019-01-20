#ifndef MATRIX_GRAPHICS_MATRIX_H
#define MATRIX_GRAPHICS_MATRIX_H

#include "vector.h"
#include <stdint.h>

#define MATRIX_SIZE 16

extern uint16_t matrix[MATRIX_SIZE];

void matrix_draw(vector_2d vec);
void matrix_basis(vector_2d *vec);

#endif
