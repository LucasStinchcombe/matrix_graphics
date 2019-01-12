#ifndef ONETWO_CONWAY_H
#define ONETWO_CONWAY_H

#include <stdint.h>

#define MATRIX_SIZE 8
extern uint8_t matrix[MATRIX_SIZE];

void matrix_init();
void send_matrix();
void next_iter();

#endif
