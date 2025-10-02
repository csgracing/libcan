#include "can/protocol/isotp/tl/handler/manager.h"

#include "can/protocol/isotp/error/code/frame_handle.h"

#include <iostream>

using can::protocol::isotp::error::code::FrameHandleError;

namespace can::protocol::isotp::tl::handler
{
    HandlerManager::HandlerManager()
    {
        active_handlers = new std::unordered_map<can::protocol::isotp::tl::pci::FrameType, BaseHandler *, can::protocol::isotp::tl::pci::FrameType::frame_type_hasher>;
    }

    bool HandlerManager::contains(can::protocol::isotp::tl::pci::FrameType type)
    {
        // note that C++20 has contains()
        return (active_handlers->find(type) != active_handlers->end());
    }

    bool HandlerManager::add(BaseHandler *handler)
    {
        can::protocol::isotp::tl::pci::FrameType key = handler->getType();

        // check if if already registered
        if (!contains(key))
        {
            // does not exist, add

            // active_handlers[key] updates if present, active_handlers.insert() skips if present
            // <https://en.cppreference.com/w/cpp/container/unordered_map/insert>

            active_handlers->insert({key, handler});
            return true;
        }
        // TODO: error handling after proof of concept phase
        return false;
    };

    boost::system::error_code HandlerManager::handle(can::protocol::classic::frame::frame_t *frame, can::protocol::isotp::link::ISOTPLink *link)
    {
        can::protocol::isotp::tl::pci::FrameType key = can::protocol::isotp::tl::pci::FrameType::GetFrameType(frame);
        // check if frame rx id is in map
        if (contains(key))
        {
            // get handler
            // ISOTPLink *link = active_links->at(frame->id);

            BaseHandler *handler = active_handlers->at(key);

            return handler->handle(frame, link);
        }
        else
        {
            return FrameHandleError::NO_HANDLER_FOR_TYPE;
        }
    };
}