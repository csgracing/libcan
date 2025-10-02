#ifndef LINK_MANAGER_H_
#define LINK_MANAGER_H_

#include <unordered_map>

#include <boost/system/error_code.hpp>

#include "can/protocol/classic/frame/identifier.h"

#include "can/protocol/isotp/link/link.h"

#include "can/protocol/isotp/tl/handler/manager.h"

namespace can::protocol::isotp::link
{
    class LinkManager
    {
    private:
        std::unordered_map<can::protocol::classic::frame::identifier, ISOTPLink *, can::protocol::classic::frame::identifier_hasher> *active_links;
        can::protocol::isotp::tl::handler::HandlerManager *handlers;

    public:
        LinkManager();
        // virtual ~LinkManager(); // destructor

        bool contains(can::protocol::classic::frame::identifier id);

        bool add(ISOTPLink *link);

        boost::system::error_code handle_receive(can::protocol::classic::frame::frame_t *frame);
    };
}

#endif /* LINK_MANAGER_H_ */