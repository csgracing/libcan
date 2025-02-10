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

        frame->dlc.dlc = raw_frame.dlc;

        // Validation done in determineType
        frame->_maxDataSize = raw_frame.data_size;
        FrameType type = FrameTypeUtil::determineType(frame);
        frame->_type = type;

        // If CAN FD or CAN FD Extended
        if ((frame->_type & FrameType::FD) == FrameType::FD)
        {
            // Copy dlc worth
            frame->_actualdataSize = FrameTypeUtil::determineDataSize(frame);

            uint8_t *fd_data_ptr = new uint8_t[frame->_actualdataSize];
            memcpy(fd_data_ptr, raw_frame.data, frame->_actualdataSize);

            frame->fd_data = fd_data_ptr;

            return *frame;
        }
        else if ((frame->_type & FrameType::CC) == FrameType::CC)
        {
            // CC or CC extended

            frame->_actualdataSize = frame->dlc.dlc;

            memcpy(&(frame->data), raw_frame.data, frame->_actualdataSize);

            return *frame;
        }
        else
        {
            // Invalid frame
            return std::nullopt;
        }
    };
}