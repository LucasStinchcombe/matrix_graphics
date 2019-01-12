#ifndef ONETWO_SPI_H
#define ONETWO_SPI_H


#include <stdint.h>

#define BIT(x, i) ((x & (1 << i)) >> i)
#define BYTE_BIT_SWAP(x) (BIT(x, 0) << 7 \
                         |BIT(x, 1) << 6 \
                         |BIT(x, 2) << 5 \
                         |BIT(x, 3) << 4 \
                         |BIT(x, 4) << 3 \
                         |BIT(x, 5) << 2 \
                         |BIT(x, 6) << 1 \
                         |BIT(x, 7) << 0)

void SPI_init();

void send_code(uint16_t code);

void SPI_slave_select();

#endif
