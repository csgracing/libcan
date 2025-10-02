#ifndef HANDLERS_SINGLE_FRAME_H_
#define HANDLERS_SINGLE_FRAME_H_

#include "can/protocol/isotp/tl/handler/base.h"
#include "can/protocol/isotp/tl/pci/frame_type.h"

namespace can::protocol::isotp::tl::handler
{
    class SingleFrameHandler : public BaseHandler
    {
    public:
        SingleFrameHandler() : BaseHandler(can::protocol::isotp::tl::pci::FrameType::SINGLE_FRAME) {};

        boost::system::error_code handle(can::protocol::classic::frame::frame_t *frame, can::protocol::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_SINGLE_FRAME_H_ */