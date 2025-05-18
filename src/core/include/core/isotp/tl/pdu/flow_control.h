#ifndef PDU_FLOW_CONTROL_H_
#define PDU_FLOW_CONTROL_H_

#include "core/isotp/tl/pci/flow_control.h"
#include "core/isotp/tl/pdu/base.h"

namespace can::isotp::tl::pdu
{
    // public Base to access parent (public) methods externally
    class FlowControl : public Base
    {
    private:
        can::isotp::tl::pci::fc::FlowStatus status;
        uint8_t block_size;
        // TODO make enum or similar (ISO spec - 9.6.5.4 Table 21)
        uint8_t separation_time;

    public:
        FlowControl(can::isotp::tl::pci::fc::FlowStatus status, uint8_t block_size, uint8_t separation_time);

        uint8_t *createPayload();
    };
}

#endif /* PDU_FLOW_CONTROL_H_ */