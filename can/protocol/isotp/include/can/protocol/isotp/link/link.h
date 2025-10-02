#ifndef LINK_LINK_H_
#define LINK_LINK_H_

#include "can/protocol/isotp/link/directional_link.h"

#include "can/protocol/classic/frame/identifier.h"
#include "can/driver/base/base.h"

namespace can::protocol::isotp::link
{

    class ISOTPLink
    {
    private:
        can::driver::base::CANBus *bus;
        DirectionalLink *send, *receive;

        moodycamel::ConcurrentQueue<can::protocol::isotp::link::directional_link_buf_t> *queue;

    public:
        ISOTPLink(can::driver::base::CANBus *bus, can::protocol::classic::frame::identifier id_tx, can::protocol::classic::frame::identifier id_rx);
        // virtual ~ISOTPLink(); // destructor

        // "getters"
        DirectionalLink *getSend() { return send; }
        DirectionalLink *getReceive() { return receive; }

        inline void setSend(DirectionalLink *entry) { this->send = entry; };
        inline void setReceive(DirectionalLink *entry) { this->receive = entry; };

        can::protocol::classic::frame::identifier getKey() { return receive->getId(); };

        can::driver::base::CANBus *getBus() { return bus; };

        // "setters"
        // void setSend(directional_entry_t *send)

        // queue
        moodycamel::ConcurrentQueue<can::protocol::isotp::link::directional_link_buf_t> *getQueue() { return this->queue; };
    };
}

#endif /* LINK_LINK_H_ */