#ifndef FRAME_FRAME_H_
#define FRAME_FRAME_H_

#include "core/protocol/frame/data.h"
#include "core/protocol/frame/dlc.h"
#include "core/protocol/frame/identifier.h"
#include "core/protocol/frame/type.h"

#include <optional>

namespace can::protocol::frame
{

    // https://github.com/KevinOConnor/can2040/blob/9e761ae353ea473e24c8bba226e10afad8a919ff/src/can2040.h#L6
    typedef struct
    {
        uint8_t _maxDataSize, _actualdataSize;
        FrameType _type;

        /**
         * CAN identifier field.
         * Per spec, use IDE bit to determine identifier length.
         */
        identifier id;

        /**
         * Remote Transmission Request bit
         */
        data::RTR rtr;

        /**
         * Identifier extension bit
         */
        data::IDE ide;

        /**
         * Extended Data Length (aka FD Format indicator)
         * 1 for CAN FD; 0 for CAN CC
         *
         * Note that in CAN CC this is a reserved bit set to 0.
         */
        data::EDL edl;

        /**
         * Data length code
         */
        dlc_s dlc;

        /**
         * CAN CC frame data.
         */
        union
        {
            uint8_t data[8];
            uint32_t data32[2];
        };

        /**
         * CAN FD frame data (if applicable)
         *
         * Data can be of variable size, up to 64 bytes inclusive.
         */
        uint8_t *fd_data;

    } frame_t;

    typedef std::optional<frame_t> frame_res;
    frame_res create(uint32_t id, bool rtr, bool ide, bool edl, uint8_t dlc, void *__restrict__ data, uint8_t data_size);
}

#endif /* FRAME_FRAME_H_ */