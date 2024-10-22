#ifndef PROVIDERS_BITRATE_H_
#define PROVIDERS_BITRATE_H_

#include <variant>

#include "rp2040/mcp2515/bitrate.h"

namespace CAN::Providers
{
    typedef std::variant<CAN::Providers::RP2040::MCP2515::Bitrate> Bitrate;
}

#endif /* PROVIDERS_BITRATE_H_ */