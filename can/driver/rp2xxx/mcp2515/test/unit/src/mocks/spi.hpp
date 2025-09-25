#ifndef MOCKS_SPI_H_
#define MOCKS_SPI_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gmock-global/gmock-global.h>

#include "hardware/gpio.stub.h"
#include "hardware/spi.h"

#include "pico/platform.h"

using namespace testing;

MOCK_GLOBAL_FUNC4(spi_read_blocking, int(spi_inst_t *, uint8_t, uint8_t *, size_t));
MOCK_GLOBAL_FUNC3(spi_write_blocking, int(spi_inst_t *, const uint8_t *, size_t));
MOCK_GLOBAL_FUNC5(spi_set_format, void(spi_inst_t *, uint, spi_cpol_t, spi_cpha_t, __unused spi_order_t)); // problematic
MOCK_GLOBAL_FUNC2(spi_init, uint(spi_inst_t *, uint));

#endif /* MOCKS_SPI_H_ */