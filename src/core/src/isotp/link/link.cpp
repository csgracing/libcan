#include "core/isotp/link/link.h"

#include "core/protocol/frame/identifier.h"

using can::protocol::frame::identifier;

namespace can::isotp::link
{
    // TODO: dynamically resize (is probably slow)
    ISOTPLink::ISOTPLink(identifier id_tx, identifier id_rx, uint32_t buf_size_tx, uint32_t buf_size_rx)
    {
        // create send, receive objects
        send = createDirectionalEntry(id_tx, buf_size_tx);
        receive = createDirectionalEntry(id_rx, buf_size_rx);

        // register in list of links
    };

    directional_entry_t *ISOTPLink::createDirectionalEntry(identifier id, uint32_t buf_size)
    {
        directional_entry_t *entry = new directional_entry_t();
        entry->id = id;
        entry->buffer_size = buf_size;

        // try not tu use malloc/calloc here, we are in CPP after all.
        entry->buffer = new uint8_t[buf_size];

        // set default status
        entry->state = LinkState::IDLE;

        return entry;
    };
}