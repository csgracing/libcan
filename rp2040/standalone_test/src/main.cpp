#include <stdlib.h>
#include <stdio.h>

#include <rp2040/mcp2515/provider.h>
#include <rp2040/mcp2515/bitrate.h>
#include <core/providers/base.h>

using namespace can::providers::rp2040::mcp2515;

int main()
{
    printf("main()\n");
    Options o;
    o.clock = Clock::MCP_16MHZ;

    CANBus cb = CANBus(Bitrate::BITRATE_1000_KBPS, o);

    return 0;
}