#ifndef HANDLERS_CONSECUTIVE_FRAME_H_
#define HANDLERS_CONSECUTIVE_FRAME_H_

#include "core/isotp/tl/handler/base.h"
#include "core/isotp/tl/pci/frame_type.h"

namespace can::isotp::tl::handler
{
    class ConsecutiveFrameHandler : public BaseHandler
    {
    public:
        ConsecutiveFrameHandler() : BaseHandler(can::isotp::tl::pci::FrameType::CONSECUTIVE_FRAME) {};

        void handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_CONSECUTIVE_FRAME_H_ */