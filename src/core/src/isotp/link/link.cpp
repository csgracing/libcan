#include "core/isotp/link/link.h"

using can::protocol::frame::identifier;

namespace can::isotp::link
{
    // TODO: dynamically resize (is probably slow)
    ISOTPLink::ISOTPLink(can::providers::base::CANBus *bus, identifier id_tx, identifier id_rx)
    {
        this->bus = bus;
        // create send, receive objects

        // create directional links w/o buffers assigned.
        // TODO: in future specify max buf size?
        send = new DirectionalLink(bus, id_tx);
        receive = new DirectionalLink(bus, id_rx);

        // register in list of links
    };
}