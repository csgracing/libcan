#include "core/isotp/tl/pdu/flow_control.h"

#include "core/isotp/tl/pci/frame_type.h"

#include "core/protocol/frame/frame.h"

#include "core/logger.h"

using can::isotp::tl::pci::FrameType;

namespace can::isotp::tl::pdu
{
    FlowControl::FlowControl(can::isotp::tl::pci::fc::FlowStatus status, uint8_t block_size, uint8_t separation_time) : Base::Base(FrameType::FLOW_CONTROL_FRAME, 3)
    {
        this->status = status;
        this->block_size = block_size;
        this->separation_time = separation_time;

        LIBCAN_LOG_TRACE("isotp.tl.pdu", "Creating FlowControl frame");
    };

    uint8_t *FlowControl::createPayload()
    {
        uint8_t *data = new uint8_t[getPayloadSize()];

        // pci_type - iso p30
        uint8_t pci_type = getType() & 0xF; // get lower 4 bits
        uint8_t flow_status = status & 0xF;

        // bits 7..4 flow_status, bits 3..0 pci_type
        // TODO mismatched endianness error potential?
        data[0] = flow_status | (pci_type << 4);
        data[1] = block_size;
        data[2] = separation_time;

        LIBCAN_LOG_DEBUG("isotp.tl.pdu", "created FC frame data of size {0:d}", getPayloadSize());

        return data;
    };
}