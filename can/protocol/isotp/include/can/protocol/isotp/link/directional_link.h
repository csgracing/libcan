#ifndef LINK_DIRECTIONAL_LINK_H_
#define LINK_DIRECTIONAL_LINK_H_

#include <string.h> // memcpy

#include "can/protocol/isotp/link/state.h"

#include "can/protocol/classic/frame/identifier.h"
#include "can/driver/base/base.h"

#include "can/protocol/isotp/tl/pci/consecutive_frame.h"

namespace can::protocol::isotp::link
{

    struct directional_link_buf_t
    {

        uint8_t *buffer;
        uint32_t size; // uint32_t (-1?) max isotp message size (theoretical)
        uint32_t offset;
        can::protocol::isotp::tl::pci::cf::SequenceNumber *sequence_number = nullptr;
    };

    class DirectionalLink
    {
    private:
        can::protocol::classic::frame::identifier id;
        LinkState state;

        // if not nullptr than assigned to something and hasBuffer will always be true
        directional_link_buf_t *buffer = nullptr;

    public:
        DirectionalLink(can::driver::base::CANBus *bus, can::protocol::classic::frame::identifier id);

        void allocateBuffer(uint32_t buf_size);

        inline bool hasBuffer()
        {
            return this->buffer != nullptr;
        };

        inline can::protocol::classic::frame::identifier getId() { return this->id; };

        inline directional_link_buf_t *getBuffer() { return this->buffer; };

        inline void setState(LinkState state) { this->state = state; };
        inline LinkState getState() { return this->state; };

        bool copyIntoBuffer(uint8_t *data, uint32_t length);
    };
};

#endif /* LINK_DIRECTIONAL_LINK_H_ */