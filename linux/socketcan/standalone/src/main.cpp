#include <iostream>

#include <core/providers/base.h>
#include <linux/socketcan/provider.h>

#include <core/isotp/tl/parse.h>

using namespace can::providers::os::socketcan;
using namespace can::providers;

int main()
{
    Options *o = new Options();
    o->canInterface = "vcan0";
    o->canProtocol = CAN_RAW;
    CANBus cb = CANBus(NULL, o);

    for (;;)
    {
        printf("attempting to read message...\r\n");
        can::protocol::frame::frame_res res = cb.readMessage();
        if (res.has_value())
        {
            can::protocol::frame::frame_t frame = res.value();
            std::wcout << "received data: ";
            for (int i = 0; i < 8; i++)
            {
                std::wcout << std::hex << frame.data[i];
            }
            std::wcout << "\r\n";
            can::isotp::tl::HandleIncomingFrame(&frame);
        };
    };

    return 0;
}