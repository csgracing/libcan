#include "core/isotp/link/manager.h"

#include <iostream> // std::wcout

namespace can::isotp::link
{
    LinkManager::LinkManager()
    {
        std::wcout << "Created new link manager\n";
        // init unordered map
        active_links = new std::unordered_map<can::protocol::frame::identifier, ISOTPLink *, can::protocol::frame::identifier_hasher>();
    };

    bool LinkManager::contains(can::protocol::frame::identifier id)
    {
        // note that C++20 has contains()
        return (active_links->find(id) != active_links->end());
    }

    bool LinkManager::add(ISOTPLink *link)
    {
        can::protocol::frame::identifier key = link->getKey();

        // check if if already registered
        if (!contains(key))
        {
            // does not exist, add

            // active_links[key] updates if present, active_links.insert() skips if present
            // <https://en.cppreference.com/w/cpp/container/unordered_map/insert>

            active_links->insert({key, link});

            std::wcout << "Added message with rx id: 0x" << std::hex << key.combined() << "\n";
            return true;
        }
        // TODO: error handling after proof of concept phase
        return false;
    };

    void LinkManager::handle_receive(can::protocol::frame::frame_t *frame)
    {
        // check if frame rx id is in map
        if (contains(frame->id))
        {
            // get handler
            // ISOTPLink *link = active_links->at(frame->id);

            can::isotp::tl::HandleIncomingFrame(frame);
        }
        else
        {
            std::wcout << "no match for id: " << std::hex << frame->id.combined() << "\n";
        }
    };
}