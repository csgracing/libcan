#include "can/protocol/isotp/link/manager.h"

#include "can/protocol/isotp/tl/handler/single_frame.h"
#include "can/protocol/isotp/tl/handler/first_frame.h"
#include "can/protocol/isotp/tl/handler/consecutive_frame.h"

#include "can/protocol/isotp/error/code/link_manager.h"

#include "can/util/log/logger.h"

using can::protocol::isotp::error::code::LinkManagerError;

using namespace can::protocol::isotp::tl;

namespace can::protocol::isotp::link
{
    LinkManager::LinkManager()
    {
        LIBCAN_LOG_DEBUG("isotp.link", "Created new link manager");
        // init unordered map
        active_links = new std::unordered_map<can::protocol::classic::frame::identifier, ISOTPLink *, can::protocol::classic::frame::identifier_hasher>();

        // register handlers
        handlers = new handler::HandlerManager();
        handlers->add(new handler::SingleFrameHandler());
        handlers->add(new handler::FirstFrameHandler());
        handlers->add(new handler::ConsecutiveFrameHandler());
    };

    bool LinkManager::contains(can::protocol::classic::frame::identifier id)
    {
        // note that C++20 has contains()
        return (active_links->find(id) != active_links->end());
    }

    bool LinkManager::add(ISOTPLink *link)
    {
        can::protocol::classic::frame::identifier key = link->getKey();

        // check if if already registered
        if (!contains(key))
        {
            // does not exist, add

            // active_links[key] updates if present, active_links.insert() skips if present
            // <https://en.cppreference.com/w/cpp/container/unordered_map/insert>

            active_links->insert({key, link});

            LIBCAN_LOG_INFO("isotp.link", "Added message with rx id: {:x}", key.combined());

            return true;
        }
        // TODO: error handling after proof of concept phase
        return false;
    };

    boost::system::error_code LinkManager::handle_receive(can::protocol::classic::frame::frame_t *frame)
    {
        // check if frame rx id is in map
        if (contains(frame->id))
        {
            // get handler
            // ISOTPLink *link = active_links->at(frame->id);

            ISOTPLink *link = active_links->at(frame->id);

            return handlers->handle(frame, link);
        }
        else
        {
            LIBCAN_LOG_DEBUG("isotp.link", "No match for id: {:x}", frame->id.combined());
            return LinkManagerError::IGNORED_ID_NOT_REGISTERED;
        }
    };
}