#ifndef TP_PARSE_H_
#define TP_PARSE_H_

#include "core/message.h"
#include "core/isotp/tl/pci/frame_type.h"

namespace can::isotp
{
    /**
     * Transport Layer [Protocol]
     * @cite ISO 15765-2:2024, 9 "Transport layer protocol"
     */
    namespace tl
    {
        /**
         * Possible packet parsing states
         * @cite ISO 15765-2:2024, 9.5.1, Figure 8 - "Verifying recieved CAN frames"
         */
        enum PacketParseStatus
        {
            /**
             * Not the correct CAN type (eg. is a CAN FD packet when we expected CAN CC)
             */
            ERROR_INCORRECT_FRAME_TYPE,

            /**
             * The CAN frame was not matched to any \link can::isotp::tl:pci::FrameType \endlink
             */
            ERROR_NOT_ISOTP_FRAME,

            /**
             * When parsing A ConsecutiveFrame, the CAN_DL was not corrrect for the determined RX_DL
             * See 9.6.4.2 for requirements
             */
            ERROR_CONSECUTIVE_FRAME_DATA_LENGTH_MISMATCH,

            SUCCESS_FIRST_FRAME,
            SUCCESS_SINGLE_FRAME,
            SUCCESS_CONSECUTIVE_FRAME,
            SUCCESS_FLOW_CONTROL_FRAME,

        };

        void HandleIncomingFrame(can::frame_t *frame);
        pci::FrameType GetFrameType(can::frame_t *frame);
        void ProcessFirstFrame(can::frame_t *frame);
    };
}

#endif /* TP_PARSE_H_ */