#ifndef MATRIX_GRAPHICS_ADC_H
#define MATRIX_GRAPHICS_ADC_H

#include <stdint.h>

void ADC_init();
uint8_t get_value(uint8_t channel);

#endif
