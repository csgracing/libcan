#ifndef FRAME_DATA_H_
#define FRAME_DATA_H_

namespace can::protocol::frame
{

    /**
     * CAN 2.0 Data Frame - bit enums
     *
     * @cite CAN 2.0 Specification, Part A, 3.1.1 "Data Frame" (page 10)
     * @cite CAN 2.0 Specification, Part B, 3.2.1 "Data Frame" (page 42)
     */
    namespace data
    {

        /**
         * Remote Transmission Request (RTR) Bit
         *
         * Note that CAN FD does not support remote frames, with the bit being referred to as reserved bit r1 and always set to dominant (0)
         *
         * @cite CAN 2.0 Specification, Part A, 3.1.1 "Data Frame" (page 11)
         * @cite CAN with Flexible Data-Rate Specification v1.0, Section 3.2.1 "Data Frame", page 11
         */
        enum RTR
        {
            /**
             * CAN frame is a Data Frame as the RTR bit is dominant (0)
             *
             * Note that CAN FD frames will always be data frames.
             */
            DATA_FRAME = 0b0,

            /**
             * CAN Frame is a Remote Frame as the RTR bit is recessive (1)
             *
             * Note that CAN FD frames canot be remote frames, remote frames in the CAN FD spec are denoted as being CAN CC frames only.
             */
            REMOTE_REQUEST_FRAME = 0b1,
        };

        /**
         * Identifier Extension (IDE) Bit
         *
         * @cite CAN 2.0 Specification, Part B, 3.2.1 "Data Frame" (page 45)
         */
        enum IDE
        {
            /**
             * CAN frame uses standard (11-bit, CAN 2.0A) addressing as the IDE bit is dominant (0)
             */
            BASE_FORMAT = 0b0,

            /**
             * CAN frame uses extended (29-bit, CAN 2.0B) addressing as the IDE bit is recessive (1)
             */
            EXTENDED_FORMAT = 0b1,
        };

        /**
         * Extended Data Length (EDL) Bit
         *
         * (aka FD Format Indicator (FDF))
         *
         * Note that in CAN CC (CAN 2.0 A or B), this bit position is reserved and is always dominant (0).
         * In CAN FD this bit (same position) is not reserved and is recessive (1) for all CAN FD frames.
         *
         * Also Note that a CAN CC frame with this bit set to 1 (FD) would technically be spec compliant as frames with either value are accepted according to the CAN CC specification.
         * Therefore, additional checks are recommended such as checking the DLC bit to determine if frame is CAN FD compliant.
         *
         * @cite CAN with Flexible Data-Rate Specification v1.0, Section 3.2 "Frame Types", page 10
         */
        enum EDL
        {
            /** CAN frame reports as being a CAN CC Frame */
            CC_FRAME = 0b0,
            /** CAN frame reports as being a CAN FD Frame */
            FD_FRAME = 0b1,
        };
    }
}

#endif /* FRAME_DATA_H_ */