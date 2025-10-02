#ifndef HANDLERS_MANAGER_H_
#define HANDLERS_MANAGER_H_

#include <boost/system/error_code.hpp>

#include "can/protocol/isotp/tl/handler/base.h"
#include "can/protocol/isotp/tl/pci/frame_type.h"

namespace can::protocol::isotp::tl::handler
{
    class HandlerManager
    {
    private:
        std::unordered_map<can::protocol::isotp::tl::pci::FrameType, BaseHandler *, can::protocol::isotp::tl::pci::FrameType::frame_type_hasher> *active_handlers;

    public:
        HandlerManager();

        bool contains(can::protocol::isotp::tl::pci::FrameType type);
        bool add(BaseHandler *handler);
        boost::system::error_code handle(can::protocol::classic::frame::frame_t *frame, can::protocol::isotp::link::ISOTPLink *link);
    };
};

#endif /* HANDLERS_MANAGER_H_ */