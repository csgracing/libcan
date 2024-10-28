#include "rp2040/mcp2515/provider.h"

#include <stdio.h>
#include <string.h> // memcpy

#include "hardware/gpio.h"

namespace can::providers::rp2040::mcp2515
{
    CANBus::CANBus(can::providers::base::bitrate_enum_t b, can::providers::base::options_t o) : can::providers::base::CANBus(b, o)
    {
        printf("MCP2515 CANBus init\n");

        this->op = static_cast<Options &>(o);
        this->chip.reset();
        CAN_SPEED speed = (CAN_SPEED)b;
        CAN_CLOCK clock = (CAN_CLOCK)this->op.clock;
        this->chip.setBitrate(speed, clock);
        this->chip.setNormalMode();
    }

    can::frame_read_res CANBus::readMessage()
    {
        struct can_frame rx;
        if (this->chip.readMessage(&rx) == MCP2515::ERROR_OK)
        {
            can::frame frame;
            frame.id = rx.can_id;
            frame.dlc = rx.can_dlc;
            memcpy(&frame.data, &rx.data, 8);
            return frame;
        }
        return std::nullopt;
    }

    void CANBus::rawIrqHandler()
    {
        if (gpio_get_irq_event_mask(this->op.interrupt_pin) & true)
        {
            gpio_acknowledge_irq(this->op.interrupt_pin, GPIO_IRQ_EDGE_FALL);

            // Read
        }
    }

    void CANBus::registerRawIrqHandlerOnCurrentCore()
    {
        uint8_t rawIsr = this->bindToNextIsrId();
        irq_handler_t func;
        switch (rawIsr)
        {
            BOOST_PP_REPEAT(MCP2515_MAX_RAW_ISR, MCP2515_ISR_SWITCH, _)
        default:
            // -1 error state from below
            printf("Failed to bind to next ISR id. Are there any free?");
            return;
        }

        gpio_add_raw_irq_handler(this->op.interrupt_pin, func);
    }

    uint8_t CANBus::bindToNextIsrId()
    {
        for (uint8_t i = 0; i < MCP2515_MAX_RAW_ISR; i++)
        {
            if (CANBus::rawIsrs[i] == NULL)
            {
                CANBus::rawIsrs[i] = this;
                return i;
            }
        }
        // error state
        return -1;
    };

    BOOST_PP_REPEAT(MCP2515_MAX_RAW_ISR, MCP2515_ISR_FUNC_IMPL, _)

    // https://stackoverflow.com/a/57504289
    CANBus::~CANBus() = default;
}