#include "mcp2515.h"

#include <stdio.h>

namespace CAN::Providers::RP2040::MCP2515
{
    CANBus::CANBus(CAN::Providers::Bitrate b, CAN::Providers::Base::Options o) : CAN::Providers::Base::CANBus(b, o)
    {
        printf("MCP2515 CANBus init\n");
    }

    // https://stackoverflow.com/a/57504289
    CANBus::~CANBus() = default;
}