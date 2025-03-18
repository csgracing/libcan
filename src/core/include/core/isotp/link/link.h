#ifndef LINK_LINK_H_
#define LINK_LINK_H_

#include "core/isotp/link/registration.h"
#include "core/protocol/frame/identifier.h"

namespace can::isotp::link
{

    class ISOTPLink
    {
    private:
        directional_entry_t *send, *receive;

        directional_entry_t *createDirectionalEntry(can::protocol::frame::identifier id, uint32_t buf_size);

    public:
        ISOTPLink(can::protocol::frame::identifier id_tx, can::protocol::frame::identifier id_rx, uint32_t buf_size_tx, uint32_t buf_size_rx);
        // virtual ~ISOTPLink(); // destructor

        // "getters"
        // directional_entry_t *getSend() { return send; }
        // directional_entry_t *getReceive() { return receive; }

        can::protocol::frame::identifier getKey() { return receive->id; };
    };
}

#endif /* LINK_LINK_H_ */