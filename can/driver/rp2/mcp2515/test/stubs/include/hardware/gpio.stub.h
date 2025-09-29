#ifndef _STUB_HARDWARE_GPIO_H
#define _STUB_HARDWARE_GPIO_H

#include <stdint.h>
#include "pico/types.h"

#include <hardware/irq.stub.h>

// include pico-sdk host hardware/gpio.h
#include <hardware/gpio.h>

uint32_t gpio_get_irq_event_mask(uint gpio);
void gpio_add_raw_irq_handler(uint gpio, irq_handler_t handler);
void gpio_acknowledge_irq(uint gpio, uint32_t event_mask);

// rp2_common/hardware_gpio
enum gpio_irq_level
{
    GPIO_IRQ_LEVEL_LOW = 0x1u,  ///< IRQ when the GPIO pin is a logical 1
    GPIO_IRQ_LEVEL_HIGH = 0x2u, ///< IRQ when the GPIO pin is a logical 0
    GPIO_IRQ_EDGE_FALL = 0x4u,  ///< IRQ when the GPIO has transitioned from a logical 0 to a logical 1
    GPIO_IRQ_EDGE_RISE = 0x8u,  ///< IRQ when the GPIO has transitioned from a logical 1 to a logical 0
};

#endif