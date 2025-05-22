#include <iostream>
#include <sstream> // std::ostringstream

#include <fmt/format.h>

#include <core/providers/base.h>
#include <linux/socketcan/provider.h>

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
    // uint32_t max_size = 8192;

    ISOTPLink *link1 = new ISOTPLink(&cb, *link1_tx, *link1_rx);

    lm->add(link1);

    for (;;)
    {
        if (cb.hasMessage())
        {
            can::protocol::frame::frame_res res = cb.readMessage();
            if (res.has_value())
            {
                can::protocol::frame::frame_t frame = res.value();

                boost::system::error_code code = lm->handle_receive(&frame);

                if (code.failed())
                {
                    std::wcout << "Err:\t" << code << " - " << code.message().c_str() << std::endl;

                    boost::system::error_condition cond = code.default_error_condition();

                    std::wcout << "Cat:\t" << cond.category().name() << " - " << cond.message().c_str() << std::endl;
                }
            };
        }

        // send messages
        cb.handleQueue();

        // handle finished isotp messages
        can::isotp::link::directional_link_buf_t msg;
        bool found = link1->getQueue()->try_dequeue(msg);

        if (found)
        {
            std::ostringstream hexData;
            for (int i = 0; i < msg.size; i++)
            {
                hexData << std::hex << (int)msg.buffer[i];
            };
            hexData << std::endl;
            std::wcout << fmt::format("Recieved isotp message of size {0:d} ({0:#x})\nData:\t{2}", msg.size, msg.size, hexData.str()).c_str();
        }
    };

    return 0;
}