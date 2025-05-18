#include "core/isotp/tl/pdu/base.h"

#include "core/isotp/tl/pci/frame_type.h"

using can::isotp::tl::pci::FrameType;

namespace can::isotp::tl::pdu
{
    Base::Base(FrameType type, uint8_t payload_size)
    {
        this->type = type;
        this->payload_size = payload_size;
    }
}