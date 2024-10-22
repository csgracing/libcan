#include <stdlib.h>
#include <stdio.h>

#include "providers/rp2040/mcp2515.h"
#include "providers/bitrate.h"

using namespace CAN::Providers::RP2040::MCP2515;

int main()
{
    printf("main()\n");
    Options o;
    o.clock = Clock::MCP_16MHZ;

    CAN::Providers::Bitrate b = Bitrate::BITRATE_1000_KBPS;

    CANBus cb = CANBus(b, o);

    return 0;
}