#include <string.h> // memcpy

#include "core/message.h"

namespace can
{

    Message::Message(uint32_t id, uint32_t dlc, void *__restrict__ data)
    {
        frame_t *frame = new frame_t();
        frame->id = id;
        frame->dlc = dlc;
        memcpy(frame->data, data, 8);

        this->frame = frame;
    };

    Message::Message(frame_t *frame)
    {
        this->frame = frame;
    };

    frame_t *Message::getFrame()
    {
        return frame;
    }

    // https://stackoverflow.com/a/57504289
    Message::~Message() = default;
}