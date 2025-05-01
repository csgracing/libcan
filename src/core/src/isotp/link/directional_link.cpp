#include "core/isotp/link/directional_link.h"

namespace can::isotp::link
{
    DirectionalLink::DirectionalLink(can::providers::base::CANBus *bus, can::protocol::frame::identifier id)
    {
        this->id = id;
        this->state = LinkState::IDLE; // default state
    };

    void DirectionalLink::allocateBuffer(uint32_t buf_size)
    {
        directional_link_buf_t *buf = new directional_link_buf_t();

        buf->sequence_number = new can::isotp::tl::pci::cf::SequenceNumber();

        buf->size = buf_size;

        buf->offset = 0;

        // try not tu use malloc/calloc here, we are in CPP after all.
        buf->buffer = new uint8_t[buf_size];

        this->buffer = buf;
    }

    bool DirectionalLink::copyIntoBuffer(uint8_t *data, uint32_t length)
    {

        if (this->hasBuffer())
        {
            // TODO better (bool/enum) error handling!
            memcpy(buffer->buffer + buffer->offset, data, length);
            buffer->offset += length;
            return true;
        }
        else
        {
            return false;
        }
    }
}