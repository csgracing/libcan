#ifndef FRAME_DLC_H_
#define FRAME_DLC_H_

#include <unordered_map>
#include <bitset>

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
    typedef std::bitset<4> dlc_t;   // 0-15
    typedef std::bitset<7> bsize_t; // 0-127

    extern std::unordered_map<bsize_t, bsize_t> dlc_mapping;
}

#endif /* FRAME_DLC_H_ */