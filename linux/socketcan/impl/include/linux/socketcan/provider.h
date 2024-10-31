#ifndef LINUX_SOCKETCAN_H_
#define LINUX_SOCKETCAN_H_

// core
#include "core/message.h"
#include "core/providers/base.h"

namespace base = can::providers::base;

// can::providers::linux throws error...
namespace can::providers::os::socketcan
{
    class CANBus : base::CANBus
    {
    public:
        CANBus(base::options_t o);
        virtual ~CANBus(); // desructor

        can::frame_read_res readMessage();
    };
}

#endif /* LINUX_SOCKETCAN_H_ */