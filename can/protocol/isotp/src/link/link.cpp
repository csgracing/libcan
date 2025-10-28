#include "can/protocol/isotp/link/link.h"

using can::protocol::classic::frame::identifier;

namespace can::protocol::isotp::link
{
    // TODO: dynamically resize (is probably slow)
    ISOTPLink::ISOTPLink(can::driver::base::CANBus *bus, identifier id_tx, identifier id_rx)
    {
        this->queue = new moodycamel::ConcurrentQueue<can::protocol::isotp::link::directional_link_buf_t>();

        this->bus = bus;
        // create send, receive objects

        // create directional links w/o buffers assigned.
        // TODO: in future specify max buf size?
        send = new DirectionalLink(bus, id_tx);
        receive = new DirectionalLink(bus, id_rx);

        // register in list of links
    };
}