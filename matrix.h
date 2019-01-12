#ifndef ONETWO_MATRIX_H
#define ONETWO_MATRIX_H

#include <stdint.h>

#define MATRIX_SIZE 8
extern uint8_t matrix[MATRIX_SIZE];

void matrix_init();
void send_matrix();
void next_iter();

#endif
