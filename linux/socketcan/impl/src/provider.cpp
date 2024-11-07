#include <stdio.h>

#include "linux/socketcan/provider.h"

#include <boost/polymorphic_cast.hpp> // boost::conversion

namespace can::providers::os::socketcan
{
    CANBus::CANBus(std::optional<base::bitrate_enum_t> b, base::Options *o) : base::CANBus(b, o)
    {
        this->op = boost::polymorphic_downcast<Options *>(o);

        if (!this->op->filterMask.has_value())
            printf("Using default param for filterMask\r\n");

        if (!this->op->defaultSenderId.has_value())
            printf("Using default param for defaultSenderId\r\n");

        CanId id(this->op->defaultSenderId.value_or(0));

        CanDriver canDriver(
            this->op->canInterface,           // canInterface | eg. [v]can[0+]
            this->op->canProtocol,            // canProtocol | eg ???
            this->op->filterMask.value_or(0), // filterMask (default 0 - match all (src: CanDriver.cpp#L81))
            id                                // default sender id (optional) (default 0 - CanDriver.hpp#L69)
        );

        this->driver = &canDriver;

        printf("Hello, world!\r\n");
    };

    can::frame_read_res CANBus::readMessage()
    {
        return std::nullopt;
    }

    CANBus::~CANBus() = default;
}