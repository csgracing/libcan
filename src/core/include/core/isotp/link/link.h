#ifndef LINK_LINK_H_
#define LINK_LINK_H_

#include "core/isotp/link/directional_link.h"

#include "core/protocol/frame/identifier.h"
#include "core/providers/base.h"

namespace can::isotp::link
{

    class ISOTPLink
    {
    private:
        can::providers::base::CANBus *bus;
        DirectionalLink *send, *receive;

    public:
        ISOTPLink(can::providers::base::CANBus *bus, can::protocol::frame::identifier id_tx, can::protocol::frame::identifier id_rx);
        // virtual ~ISOTPLink(); // destructor

        // "getters"
        DirectionalLink *getSend() { return send; }
        DirectionalLink *getReceive() { return receive; }

        inline void setSend(DirectionalLink *entry) { this->send = entry; };
        inline void setReceive(DirectionalLink *entry) { this->receive = entry; };

        can::protocol::frame::identifier getKey() { return receive->getId(); };

        can::providers::base::CANBus *getBus() { return bus; };

        // "setters"
        // void setSend(directional_entry_t *send)
    };
}

#endif /* LINK_LINK_H_ */