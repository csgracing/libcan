#include <string.h> // memcpy

#include "core/protocol/frame/frame.h"
#include "core/protocol/frame/util.h" // FrameTypeUtil

using namespace can::protocol::frame::data;

namespace can::protocol::frame
{
    frame_res create(uint32_t id, bool rtr, bool ide, bool edl, uint8_t dlc, void *__restrict__ data, uint8_t data_size)
    {
        // Create a new frame struct.
        frame_t *frame = new frame_t();

        // Set variables excluding data
        frame->id.base = id & 0b11111111111;
        frame->id.extended = id >> 11;

        frame->rtr = rtr ? RTR::REMOTE_REQUEST_FRAME : RTR::DATA_FRAME;
        frame->ide = ide ? IDE::EXTENDED_FORMAT : IDE::BASE_FORMAT;
        frame->edl = edl ? EDL::FD_FRAME : EDL::CC_FRAME;

        frame->dlc.dlc = dlc;

        // Validation done in determineType
        frame->_maxDataSize = data_size;
        FrameType type = FrameTypeUtil::determineType(frame);
        frame->_type = type;

        // If CAN FD or CAN FD Extended
        if ((frame->_type & FrameType::FD) == FrameType::FD)
        {
            // Copy dlc worth
            frame->_actualdataSize = FrameTypeUtil::determineDataSize(frame);

            uint8_t *fd_data_ptr = new uint8_t[frame->_actualdataSize];
            memcpy(fd_data_ptr, data, frame->_actualdataSize);

            frame->fd_data = fd_data_ptr;

            return *frame;
        }
        else if ((frame->_type & FrameType::CC) == FrameType::CC)
        {
            // CC or CC extended

            frame->_actualdataSize = frame->dlc.dlc;

            memcpy(&(frame->data), data, frame->_actualdataSize);

            return *frame;
        }
        else
        {
            // Invalid frame
            return std::nullopt;
        }
    };
}