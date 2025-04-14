#include "core/isotp/tl/pdu/flow_control.h"

#include <iostream> // std::wcout (temp)

#include "core/isotp/tl/pci/frame_type.h"

#include "core/protocol/frame/frame.h"

using can::isotp::tl::pci::FrameType;

namespace can::isotp::tl::pdu
{
    FlowControl::FlowControl(can::isotp::tl::pci::fc::FlowStatus status, uint8_t block_size, uint8_t separation_time) : Base::Base(FrameType::FLOW_CONTROL_FRAME, 3)
    {
        this->status = status;
        this->block_size = block_size;
        this->separation_time = separation_time;

        std::wcout << "Creating FC frame..." << std::endl;
    };

    uint8_t *FlowControl::createPayload()
    {
        uint8_t *data = new uint8_t[getPayloadSize()];

        // pci_type - iso p30
        uint8_t pci_type = getType() & 0xF; // get lower 4 bits
        uint8_t flow_status = status & 0xF;

        // bits 7..4 flow_status, bits 3..0 pci_type
        // TODO mismatched endianness error potential?
        data[0] = pci_type | (flow_status << 4);
        data[1] = block_size;
        data[2] = separation_time;

        std::wcout << "created FC frame data of size " << std::dec << getPayloadSize() << std::endl;

        // temp: print data
        for (int i = 0; i < 3; i++)
        {
            std::wcout << std::hex << data[i];
        }
        std::wcout << std::endl;

        return data;
    };
}