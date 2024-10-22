#ifndef RP2040_MCP2515_H_
#define RP2040_MCP2515_H_

#include <type_traits> //for std::underlying_type

#include "mcp2515/bitrate.h"

#include "../base.h"
#include "../bitrate.h"

namespace CAN::Providers::RP2040::MCP2515
{

    // implementation specific

    // Src: https://github.com/adamczykpiotr/pico-mcp2515/blob/4506dd0659b37b35eaf411de2d93669da471f6c4/include/mcp2515/mcp2515.h#L176C1-L180C3
    enum Clock
    {
        MCP_20MHZ,
        MCP_16MHZ,
        MCP_8MHZ
    };

    struct Options : CAN::Providers::Base::Options
    {
        Clock clock;
    };

    class CANBus : CAN::Providers::Base::CANBus
    {
    public:
        CANBus(CAN::Providers::Bitrate b, CAN::Providers::Base::Options o);
        virtual ~CANBus(); // desructor
    };
};

#endif /* RP2040_MCP2515_H_ */