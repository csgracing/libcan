#include "core/protocol/frame/util.h"

#include "core/protocol/frame/frame.h"
#include "core/protocol/frame/data.h"

namespace can::protocol::frame
{
    bsize_t FrameTypeUtil::determineDataSize(frame_t *frame)
    {
        bsize_t dlcCasted = frame->dlc.to_ulong();
        if ((frame->_type & FrameType::CC) == FrameType::CC)
        {
            return dlcCasted;
        }
        else if ((frame->_type & FrameType::FD) == FrameType::FD)
        {
            if (frame->dlc.to_ulong() > 8)
            {
                return dlc_mapping.at(dlcCasted);
            }
            else
            {
                return dlcCasted;
            }
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
        long dlc_l = frame->dlc.to_ulong();
        long bsize_l = frame->_bsize.to_ulong();
        // DLC 0 through 8 inclusive
        if (0 <= dlc_l && dlc_l <= 8)
        {
            // Check if frame reports as a CC frame with max size != 8
            if (bsize_l != 8 && frame->edl == data::EDL::CC_FRAME)
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
        if (9 <= dlc_l && dlc_l <= 15)
        {
            // payload 8 bytes
            if (bsize_l == 8)
            {
                // CAN CC frame with >8 DLC (edge case where DLC will be capped at 8)
                // call func to determine if extended format
                return determineIfExtendedFormat(frame, CC);
            }

            // payload 12 through 64 bytes inclusive
            if (12 <= bsize_l && bsize_l <= 64)
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