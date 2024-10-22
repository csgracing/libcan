#include "rp2040/mcp2515/provider.h"

#include <stdio.h>

namespace can::providers::rp2040::mcp2515
{
    CANBus::CANBus(can::providers::base::bitrate_enum_t b, can::providers::base::Options o) : can::providers::base::CANBus(b, o)
    {
        printf("MCP2515 CANBus init\n");
    }

    // https://stackoverflow.com/a/57504289
    CANBus::~CANBus() = default;
}