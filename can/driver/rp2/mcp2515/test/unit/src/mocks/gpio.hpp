#ifndef MOCKS_GPIO_H_
#define MOCKS_GPIO_H_

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <gmock-global/gmock-global.h>

#include "hardware/gpio.stub.h"

#include "pico/platform.h"

using namespace testing;

// static inline uint32_t gpio_get_irq_event_mask(uint gpio);
MOCK_GLOBAL_FUNC1(gpio_get_irq_event_mask, uint32_t(uint));
MOCK_GLOBAL_FUNC2(gpio_add_raw_irq_handler, void(uint, irq_handler_t));
MOCK_GLOBAL_FUNC2(gpio_acknowledge_irq, void(uint, uint32_t));

#endif /* MOCKS_GPIO_H_ */