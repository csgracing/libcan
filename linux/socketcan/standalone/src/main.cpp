#include <iostream>

#include <core/providers/base.h>
#include <linux/socketcan/provider.h>

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
        printf("hello\r\n");
        can::frame_read_res res = cb.readMessage();
        if (res.has_value())
        {
            can::frame frame = res.value();
            std::wcout << "data: ";
            for (int i = 0; i < 8; i++)
            {
                std::wcout << std::hex << frame.data[i];
            }
            std::wcout << "\r\n";
        };
    };

    return 0;
}