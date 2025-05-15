#ifndef LINK_MANAGER_H_
#define LINK_MANAGER_H_

#include <unordered_map>

#include <boost/system/error_code.hpp>

#include "core/protocol/frame/identifier.h"

#include "core/isotp/link/link.h"

#include "core/isotp/tl/handler/manager.h"

namespace can::isotp::link
{
    class LinkManager
    {
    private:
        std::unordered_map<can::protocol::frame::identifier, ISOTPLink *, can::protocol::frame::identifier_hasher> *active_links;
        can::isotp::tl::handler::HandlerManager *handlers;

    public:
        LinkManager();
        // virtual ~LinkManager(); // destructor

        bool contains(can::protocol::frame::identifier id);

        bool add(ISOTPLink *link);

        boost::system::error_code handle_receive(can::protocol::frame::frame_t *frame);
    };
}

#endif /* LINK_MANAGER_H_ */