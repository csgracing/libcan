#ifndef RP2040_MCP2515_H_
#define RP2040_MCP2515_H_

#include <type_traits> //for std::underlying_type

// core
#include "core/message.h"
#include "core/providers/base.h"

namespace can::providers::rp2040::mcp2515
{

    // implementation specific

    // Src: https://github.com/adamczykpiotr/pico-mcp2515/blob/4506dd0659b37b35eaf411de2d93669da471f6c4/include/mcp2515/mcp2515.h#L176C1-L180C3
    enum Clock
    {
        MCP_20MHZ,
        MCP_16MHZ,
        MCP_8MHZ
    };

    struct Options : can::providers::base::Options
    {
        Clock clock;
    };

    class CANBus : can::providers::base::CANBus
    {
    public:
        CANBus(can::providers::base::bitrate_enum_t b, can::providers::base::Options o);
        virtual ~CANBus(); // desructor
    };
}

#endif /* RP2040_MCP2515_H_ */