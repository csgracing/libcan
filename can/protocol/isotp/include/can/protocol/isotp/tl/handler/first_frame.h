#ifndef HANDLERS_FIRST_FRAME_H_
#define HANDLERS_FIRST_FRAME_H_

#include "can/protocol/isotp/tl/handler/base.h"
#include "can/protocol/isotp/tl/pci/frame_type.h"

namespace can::protocol::isotp::tl::handler
{
    class FirstFrameHandler : public BaseHandler
    {
    public:
        FirstFrameHandler() : BaseHandler(can::protocol::isotp::tl::pci::FrameType::FIRST_FRAME) {};

        boost::system::error_code handle(can::protocol::classic::frame::frame_t *frame, can::protocol::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_FIRST_FRAME_H_ */