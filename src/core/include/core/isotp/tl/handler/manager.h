#ifndef HANDLERS_MANAGER_H_
#define HANDLERS_MANAGER_H_

#include "core/isotp/tl/handler/base.h"
#include "core/isotp/tl/pci/frame_type.h"

namespace can::isotp::tl::handler
{
    class HandlerManager
    {
    private:
        std::unordered_map<can::isotp::tl::pci::FrameType, BaseHandler *, can::isotp::tl::pci::FrameType::frame_type_hasher> *active_handlers;

    public:
        HandlerManager();

        bool contains(can::isotp::tl::pci::FrameType type);
        bool add(BaseHandler *handler);
        void handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_MANAGER_H_ */