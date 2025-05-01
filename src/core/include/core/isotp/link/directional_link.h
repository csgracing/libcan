#ifndef LINK_DIRECTIONAL_LINK_H_
#define LINK_DIRECTIONAL_LINK_H_

#include <string.h> // memcpy

#include "core/isotp/link/state.h"

#include "core/protocol/frame/identifier.h"
#include "core/providers/base.h"

#include "core/isotp/tl/pci/consecutive_frame.h"

namespace can::isotp::link
{

    struct directional_link_buf_t
    {

        uint8_t *buffer;
        uint32_t size; // uint32_t (-1?) max isotp message size (theoretical)
        uint32_t offset;
        can::isotp::tl::pci::cf::SequenceNumber *sequence_number;
    };

    class DirectionalLink
    {
    private:
        can::protocol::frame::identifier id;
        LinkState state;

        directional_link_buf_t *buffer;

    public:
        DirectionalLink(can::providers::base::CANBus *bus, can::protocol::frame::identifier id);

        void allocateBuffer(uint32_t buf_size);

        inline bool hasBuffer()
        {
            return this->buffer != nullptr;
        };

        inline can::protocol::frame::identifier getId() { return this->id; };

        inline directional_link_buf_t *getBuffer() { return this->buffer; };

        inline void setState(LinkState state) { this->state = state; };
        inline LinkState getState() { return this->state; };

        bool copyIntoBuffer(uint8_t *data, uint32_t length);
    };
};

#endif /* LINK_DIRECTIONAL_LINK_H_ */