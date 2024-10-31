#include <stdio.h>

#include "linux/socketcan/provider.h"

namespace can::providers::os::socketcan
{
    CANBus::CANBus(base::options_t o) : base::CANBus(NULL, o)
    {
        printf("Hello, world!");
    };

    can::frame_read_res CANBus::readMessage()
    {
        return std::nullopt;
    }

    CANBus::~CANBus() = default;
}