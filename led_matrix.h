#ifndef ONETWO_LED_MATRIX_H
#define ONETWO_LED_MATRIX_H
#include "matrix.h"

void matrix_init();
void send_matrix();
void send_matrix_code(uint16_t code);
void pulse_matrix();

#endif
