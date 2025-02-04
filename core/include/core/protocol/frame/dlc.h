#ifndef FRAME_DLC_H_
#define FRAME_DLC_H_

#include <unordered_map>

#include <stdint.h> // uint[x]_t

namespace can::protocol::frame
{
    /**
     * CAN data length code.
     *
     * For CAN CC, 0-8 inclusive.
     * For CAN FD, 0-15 inclusive where a DLC > 8 are translated to values 12 through 64 inclusive.
     *
     */
    struct dlc_s
    {
        uint8_t dlc : 4;
    };

    extern std::unordered_map<uint8_t, uint8_t> dlc_mapping;
}

#endif /* FRAME_DLC_H_ */