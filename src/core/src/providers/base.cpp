#include <stdio.h>
#include <iostream> // std::wcout

#include "core/providers/base.h"

namespace can::providers::base
{
    CANBus::CANBus(std::optional<bitrate_enum_t> b, Options *o)
    {
        printf("CANBus Base init\n");
    }

    // https://stackoverflow.com/a/57504289
    CANBus::~CANBus() = default;

    can::protocol::frame::frame_res CANBus::createFrame(can::protocol::frame::identifier id, uint8_t *data, uint8_t data_length)
    {
        // PoC using create()
        // todo refactor frame_t.
        can::protocol::frame::frame_raw_t raw_frame = {
            id.combined(),
            false,              // rtr
            (id.extended != 0), // ide (true if extended arr set)
            false,              // edl (TODO: only can CC for now)
            data_length,
            data,
            8};

        return can::protocol::frame::create(raw_frame);
    }

    void CANBus::handleQueue()
    {
        can::protocol::frame::frame_t frame;

        bool found = queue.try_dequeue(frame);

        if (found)
        {
            std::wcout << "Found message." << std::endl;
            sendMessage(frame);
        }
    }

    bool CANBus::enqueue(can::protocol::frame::frame_t frame)
    {
        return queue.enqueue(frame);
    }
}