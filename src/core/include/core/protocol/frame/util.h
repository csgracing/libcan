#ifndef FRAME_UTIL_H_
#define FRAME_UTIL_H_

#include <cstdint>

#include "core/protocol/frame/frame.h"

namespace can::protocol::frame
{
    class FrameTypeUtil
    {
    public:
        static bsize_t determineDataSize(frame_t *frame);
        static FrameType determineIfExtendedFormat(frame_t *frame, FrameType type);
        static FrameType determineType(frame_t *frame);
    };
}

#endif /* FRAME_UTIL_H_ */