#include "rp2040/mcp2515/provider.h"

#include <stdio.h>
#include <string.h> // memcpy

#ifdef IS_TEST_ENV
#include "hardware/gpio.stub.h"
#else
#include "hardware/gpio.h"
#endif

namespace can::providers::rp2040::mcp2515
{
    CANBus::CANBus(std::optional<can::providers::base::bitrate_enum_t> b, can::providers::base::options_t o) : CANBusInterface(b, o)
    {
        printf("MCP2515 CANBus init\n");

        this->op = static_cast<Options &>(o);
        this->chip.reset();

        ::mcp2515::CAN_SPEED speed;

        if (b.has_value())
        {
            speed = (::mcp2515::CAN_SPEED)b.value();
        }
        else
        {
            printf("Required param speed not set, defaulting to 1Mbit/s");
            speed = ::mcp2515::CAN_1000KBPS;
        }

        ::mcp2515::CAN_CLOCK clock = (::mcp2515::CAN_CLOCK)this->op.clock;
        this->chip.setBitrate(speed, clock);
        this->chip.setNormalMode();
    }

    can::frame_read_res CANBus::readMessage()
    {
        ::mcp2515::can_frame rx;
        if (this->chip.readMessage(&rx) == ::mcp2515::MCP2515::ERROR_OK)
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

            // Ready
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
            if (CANBus::rawIsrs[i] == nullptr)
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