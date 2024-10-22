#include <stdio.h>

#include "base.h"

namespace CAN::Providers::Base
{
    CANBus::CANBus(CAN::Providers::Bitrate b, Options o)
    {
        printf("CANBus Base init\n");
    }

    // https://stackoverflow.com/a/57504289
    CANBus::~CANBus() = default;
}