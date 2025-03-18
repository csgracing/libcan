#ifndef LINK_REGISTRATION_H_
#define LINK_REGISTRATION_H_

#include "core/protocol/frame/identifier.h"
#include "core/isotp/tl/parse.h"

namespace can::isotp::link
{

    enum LinkState
    {
        IDLE, // DEFAULT
        IN_PROGRESS,
        ERROR, // todo expand
    };

    struct directional_entry_t
    {
        can::protocol::frame::identifier id;

        uint8_t *buffer;
        uint32_t buffer_size; // uint32_t (-1?) max isotp message size (theoretical)
        LinkState state;
    };
}

#endif /* LINK_REGISTRATION_H_ */