#ifndef FRAME_TYPE_H_
#define FRAME_TYPE_H_

#include <cstdint>

namespace can::protocol::frame
{
    enum FrameType
    {
        INVALID = 0b0000,
        UNKNOWN_EXTENDED = 0b0100, // extended, but valid frame (TODO rename this!)
        // [one if valid][extended][cc][fd]
        CC = 0b1010,
        CC_EXTENDED = 0b1110,
        FD = 0b1001,
        FD_EXTENDED = 0b1101,
    };

    inline bool isType(FrameType expected, FrameType includes)
    {
        return ((expected & includes) == includes);
    };
}

#endif /* FRAME_TYPE_H_ */