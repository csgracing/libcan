#ifndef HANDLERS_SINGLE_FRAME_H_
#define HANDLERS_SINGLE_FRAME_H_

#include "core/isotp/tl/handler/base.h"
#include "core/isotp/tl/pci/frame_type.h"

namespace can::isotp::tl::handler
{
    class SingleFrameHandler : public BaseHandler
    {
    public:
        SingleFrameHandler() : BaseHandler(can::isotp::tl::pci::FrameType::SINGLE_FRAME) {};

        boost::system::error_code handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_SINGLE_FRAME_H_ */