#ifndef HANDLERS_BASE_H_
#define HANDLERS_BASE_H_

#include <memory>

#include <iostream>
#include "core/isotp/link/link.h"
#include "core/isotp/tl/pci/frame_type.h"
#include "core/protocol/frame/frame.h"

namespace can::isotp::tl::handler
{
    class BaseHandler
    {
    private:
        can::isotp::tl::pci::FrameType type;

    public:
        BaseHandler(can::isotp::tl::pci::FrameType type) { this->type = type; };

        // virtual ~BaseHandler();

        virtual void handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link) = 0;

        inline can::isotp::tl::pci::FrameType getType() { return this->type; };
    };
};

#endif /* HANDLERS_BASE_H_ */