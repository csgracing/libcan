#ifndef _STUB_HARDWARE_SPI_H
#define _STUB_HARDWARE_SPI_H

#include <stdint.h>

#include "pico/types.h"
#include "pico/platform.h"

#include "stddef.h"

typedef struct spi_inst spi_inst_t;

#define spi0 ((spi_inst_t *)nullptr)

typedef enum
{
    SPI_CPHA_0 = 0,
    SPI_CPHA_1 = 1
} spi_cpha_t;

typedef enum
{
    SPI_CPOL_0 = 0,
    SPI_CPOL_1 = 1
} spi_cpol_t;

typedef enum
{
    SPI_LSB_FIRST = 0,
    SPI_MSB_FIRST = 1
} spi_order_t;

extern int spi_write_read_blocking(spi_inst_t *spi, const uint8_t *src, uint8_t *dst, size_t len);
extern int spi_read_blocking(spi_inst_t *spi, uint8_t repeated_tx_data, uint8_t *dst, size_t len);
extern int spi_write_blocking(spi_inst_t *spi, const uint8_t *src, size_t len);
static void spi_set_format(spi_inst_t *spi, uint data_bits, spi_cpol_t cpol, spi_cpha_t cpha, __unused spi_order_t order);
extern uint spi_init(spi_inst_t *spi, uint baudrate);

#endif