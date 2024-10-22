#ifndef PROVIDERS_BASE_H_
#define PROVIDERS_BASE_H_

#define BITS_IN_KB 1000

#include "bitrate.h"

namespace CAN::Providers::Base
{

    struct Options
    {
    };

    class CANBus
    {
    public:
        CANBus(CAN::Providers::Bitrate b, Options o);
        virtual ~CANBus(); // desructor
    };
};

#endif /* PROVIDERS_BASE_H_ */