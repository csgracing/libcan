#include <stdio.h>

#include "core/providers/base.h"

namespace can::providers::base
{
    CANBus::CANBus(bitrate_enum_t b, options_t o)
    {
        printf("CANBus Base init\n");
    }

    // https://stackoverflow.com/a/57504289
    CANBus::~CANBus() = default;
}