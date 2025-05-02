#ifndef HANDLERS_FIRST_FRAME_H_
#define HANDLERS_FIRST_FRAME_H_

#include "core/isotp/tl/handler/base.h"
#include "core/isotp/tl/pci/frame_type.h"

namespace can::isotp::tl::handler
{
    class FirstFrameHandler : public BaseHandler
    {
    public:
        FirstFrameHandler() : BaseHandler(can::isotp::tl::pci::FrameType::FIRST_FRAME) {};

        void handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_FIRST_FRAME_H_ */