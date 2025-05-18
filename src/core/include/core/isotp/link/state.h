#ifndef LINK_STATE_H_
#define LINK_STATE_H_

namespace can::isotp::link
{

    enum LinkState
    {
        IDLE, // DEFAULT
        IN_PROGRESS,
        FULL,  // only RX
        ERROR, // only TX: todo expand
    };
}

#endif /* LINK_STATE_H_ */