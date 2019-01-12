#ifndef ONETWO_SPI_H
#define ONETWO_SPI_H

#include <stdint.h>

void SPI_init();

void send_code(uint16_t code);

void SPI_slave_select();

#endif
