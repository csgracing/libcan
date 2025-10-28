#include "can/protocol/isotp/tl/pdu/base.h"

#include "can/protocol/isotp/tl/pci/frame_type.h"

using can::protocol::isotp::tl::pci::FrameType;

namespace can::protocol::isotp::tl::pdu
{
    Base::Base(FrameType type, uint8_t payload_size)
    {
        this->type = type;
        this->payload_size = payload_size;
    }
}