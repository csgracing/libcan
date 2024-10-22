#ifndef MCP2515_BITRATE_H_
#define MCP2515_BITRATE_H_

namespace CAN::Providers::RP2040::MCP2515
{
    enum Bitrate
    {
        BITRATE_5_KBPS,
        BITRATE_10_KBPS,
        BITRATE_20_KBPS,
        BITRATE_31K25BPS,
        BITRATE_33_KBPS,
        BITRATE_40_KBPS,
        BITRATE_50_KBPS,
        BITRATE_80_KBPS,
        BITRATE_83K3BPS,
        BITRATE_95_KBPS,
        BITRATE_100_KBPS,
        BITRATE_125_KBPS,
        BITRATE_200_KBPS,
        BITRATE_250_KBPS,
        BITRATE_500_KBPS,
        BITRATE_1000_KBPS
    };
}

#endif /* MCP2515_BITRATE_H_ */