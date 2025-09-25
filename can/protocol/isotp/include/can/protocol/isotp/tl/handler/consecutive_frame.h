#ifndef HANDLERS_CONSECUTIVE_FRAME_H_
#define HANDLERS_CONSECUTIVE_FRAME_H_

#include "can/protocol/isotp/tl/handler/base.h"
#include "can/protocol/isotp/tl/pci/frame_type.h"

namespace can::isotp::tl::handler
{
    class ConsecutiveFrameHandler : public BaseHandler
    {
    public:
        ConsecutiveFrameHandler() : BaseHandler(can::isotp::tl::pci::FrameType::CONSECUTIVE_FRAME) {};

        boost::system::error_code handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_CONSECUTIVE_FRAME_H_ */