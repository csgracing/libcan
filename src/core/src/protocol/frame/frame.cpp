#include <string.h> // memcpy

#include "core/protocol/frame/frame.h"
#include "core/protocol/frame/util.h" // FrameTypeUtil

using namespace can::protocol::frame::data;

namespace can::protocol::frame
{
    frame_res create(frame_raw_t raw_frame)
    {
        // Create a new frame struct.
        frame_t *frame = new frame_t();

        // Set variables excluding data
        frame->id.base = raw_frame.id & 0b11111111111;
        frame->id.extended = raw_frame.id >> 11;

        frame->rtr = raw_frame.rtr ? RTR::REMOTE_REQUEST_FRAME : RTR::DATA_FRAME;
        frame->ide = raw_frame.ide ? IDE::EXTENDED_FORMAT : IDE::BASE_FORMAT;
        frame->edl = raw_frame.edl ? EDL::FD_FRAME : EDL::CC_FRAME;

        if (raw_frame.dlc >> 4 != 0)
        {
            // larger than 15 (0b0000), therefore we have an overflowed dlc bit
            return std::nullopt;
        }

        frame->dlc = std::bitset<4>(raw_frame.dlc);

        // Validation done in determineType
        frame->_bsize = raw_frame.size_bytes;
        FrameType type = FrameTypeUtil::determineType(frame);
        frame->_type = type;

        // If CAN FD or CAN FD Extended
        if ((frame->_type & FrameType::FD) == FrameType::FD)
        {
            // check if reports as remote frame (not valid for FD frames)
            if (frame->rtr == RTR::REMOTE_REQUEST_FRAME)
            {
                return std::nullopt;
            }

            // Copy dlc worth
            frame->_bsize = FrameTypeUtil::determineDataSize(frame);

            uint8_t *fd_data_ptr = new uint8_t[frame->_bsize.to_ulong()];
            memcpy(fd_data_ptr, raw_frame.data, frame->_bsize.to_ulong());

            frame->fd_data = fd_data_ptr;

            return *frame;
        }
        else if ((frame->_type & FrameType::CC) == FrameType::CC)
        {
            // CC or CC extended

            if (frame->dlc.to_ulong() > 8)
            {
                // edge case: can cc frames with dlc >=8 will have their dlc capped at 8
                // then will be processed as usual
                frame->_bsize = std::bitset<7>(8);
            }
            else
            {
                frame->_bsize = std::bitset<7>(frame->dlc.to_ulong());
            }

            memcpy(&(frame->data), raw_frame.data, frame->_bsize.to_ulong());

            return *frame;
        }
        else
        {
            // Invalid frame
            return std::nullopt;
        }
    };
}