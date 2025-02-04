#include "core/protocol/frame/dlc.h"

namespace can::protocol::frame
{
    std::unordered_map<uint8_t, uint8_t> dlc_mapping = {
        {9, 12},
        {10, 16},
        {11, 20},
        {12, 24},
        {13, 32},
        {14, 48},
        {15, 64},
    };
}