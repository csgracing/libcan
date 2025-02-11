#include "core/protocol/frame/util.h"

#include "core/protocol/frame/frame.h"
#include "core/protocol/frame/data.h"

namespace can::protocol::frame
{
    uint8_t FrameTypeUtil::determineDataSize(frame_t *frame)
    {
        if (frame->_type & FrameType::CC)
        {
            return frame->dlc.dlc;
        }
        else if (frame->_type & FrameType::FD)
        {
            return dlc_mapping.at(frame->dlc.dlc);
        }
        else
        {
            // datatype none of the above or not set
            // TODO: better handling? silently fails rn...
            return 0;
        }
    };

    /**
     * Should be called with type as either CC or FD. Will determine and return
     * (orig)_EXTENDED or calling/orig value, or invalid
     */
    FrameType FrameTypeUtil::determineIfExtendedFormat(frame_t *frame, FrameType type)
    {
        if (frame->ide == data::IDE::BASE_FORMAT && frame->id.extended != 0)
        {
            // frame reports as non-extended but extended ID set, invalid
            return INVALID;
        }
        else
        {
            // frame is either valid extended or base
            // return based on IDE frame
            if (type == CC)
            {
                return (frame->ide == data::IDE::BASE_FORMAT) ? CC : CC_EXTENDED;
            }
            else
            {
                // FD
                return (frame->ide == data::IDE::BASE_FORMAT) ? FD : FD_EXTENDED;
            }
        }
    };

    FrameType FrameTypeUtil::determineType(frame_t *frame)
    {
        // DLC 0 through 8 inclusive
        if (0 <= frame->dlc.dlc && frame->dlc.dlc <= 8)
        {
            // Check if frame reports as a CC frame with max size != 8
            if (frame->_maxDataSize != 8 && frame->edl == data::EDL::CC_FRAME)
            {
                // Invalid, CC frame incorrect max data size.
                return INVALID;
            }
            else
            {
                // could be either CC or FD

                // trust EDL, call func to determine if extended format
                FrameType ccOrFd = frame->edl == data::EDL::CC_FRAME ? CC : FD;
                return determineIfExtendedFormat(frame, ccOrFd);
            }
        }

        // DLC 9 through 15 inclusive
        if (9 <= frame->dlc.dlc && frame->dlc.dlc <= 15)
        {
            // payload 8 bytes
            if (frame->_maxDataSize == 8)
            {
                // CAN CC frame with >8 DLC (edge case where DLC will be capped at 8)
                // call func to determine if extended format
                return determineIfExtendedFormat(frame, CC);
            }

            // payload 12 through 64 bytes inclusive
            if (12 <= frame->_maxDataSize && frame->_maxDataSize <= 64)
            {
                // cannot be CC frame
                if (frame->rtr == data::RTR::DATA_FRAME)
                {
                    // CAN FD Frame
                    // call func to determine if extended format
                    return determineIfExtendedFormat(frame, FD);
                }
                else
                {
                    // else is "FD" reporting remote frame, invalid
                    return INVALID;
                }
            }
        }

        return INVALID;
    };
}