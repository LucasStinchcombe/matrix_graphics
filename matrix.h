#ifndef ONETWO_MATRIX_H
#define ONETWO_MATRIX_H

#include "vector.h"
#include <stdint.h>

#define MATRIX_SIZE 16

extern uint16_t matrix[MATRIX_SIZE];

void matrix_init();
void send_matrix();
void send_matrix_code(uint16_t code);
void matrix_draw(vector_2d vec);
void pulse_matrix();

#endif
