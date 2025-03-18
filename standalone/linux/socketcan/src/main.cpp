#include <iostream>

#include <core/providers/base.h>
#include <linux/socketcan/provider.h>

#include <core/isotp/tl/parse.h>
#include <core/isotp/link/manager.h>

using namespace can::providers::os::socketcan;
using namespace can::providers;

using namespace can::isotp::link;

using can::protocol::frame::identifier;

int main()
{
    Options *o = new Options();
    o->canInterface = "vcan0";
    o->canProtocol = CAN_RAW;
    CANBus cb = CANBus(NULL, o);

    // isotp init
    LinkManager *lm = new LinkManager();

    identifier *link1_tx = new identifier(0x123);
    identifier *link1_rx = new identifier(0x124);
    uint32_t max_size = 8192;

    ISOTPLink *link1 = new ISOTPLink(*link1_tx, *link1_rx, max_size, max_size);

    lm->add(link1);

    for (;;)
    {
        if (cb.hasMessage())
        {
            printf("\r\nattempting to read message...\r\n");
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
                std::wcout << std::hex << frame.id.combined() << "\n";
                // can::isotp::tl::HandleIncomingFrame(&frame);

                lm->handle_receive(&frame);
            };
        }
    };

    return 0;
}