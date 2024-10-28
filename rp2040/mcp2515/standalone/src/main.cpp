#include <stdlib.h>
#include <stdio.h>

#include <rp2040/mcp2515/provider.h>
#include <core/providers/base.h>

using namespace can::providers::rp2040::mcp2515;
using namespace can::providers;

int main()
{
    printf("main()\n");
    rp2040::mcp2515::Options o;
    o.clock = rp2040::mcp2515::Clock::CLOCK_16_MHZ;

    CANBus cb = CANBus(
        (base::bitrate_enum_t)Bitrate::BITRATE_1000000,
        (base::options_t)o);

    can::frame_read_res msg = cb.readMessage();

    return 0;
}