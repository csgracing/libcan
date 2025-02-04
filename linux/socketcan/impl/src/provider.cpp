#include <stdio.h>

#include "linux/socketcan/provider.h"

#include <boost/polymorphic_cast.hpp> // boost::conversion

using std::chrono::milliseconds;

using sockcanpp::CanMessage;

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

        this->driver = new CanDriver(
            this->op->canInterface,           // canInterface | eg. [v]can[0+]
            this->op->canProtocol,            // canProtocol | eg ???
            this->op->filterMask.value_or(0), // filterMask (default 0 - match all (src: CanDriver.cpp#L81))
            id                                // default sender id (optional) (default 0 - CanDriver.hpp#L69)
        );
    };

    can::protocol::frame::frame_res CANBus::readMessage()
    {
        // Set timeout to whatever was passed in options, otherwise defaulting to 3 seconds.
        milliseconds timeout = this->op->readTimeout.value_or(milliseconds(3000));

        if (this->driver->waitForMessages(timeout))
        {
            // There is a message available
            CanMessage recvMessage = this->driver->readMessage();

            // Get linux internal can_frame
            can_frame linuxFrame = recvMessage.getRawFrame();

            return can::protocol::frame::create(
                linuxFrame.can_id >> 3,                    // id: bits 0-28 (shift out 29,30,31)
                linuxFrame.can_id & CAN_RTR_FLAG,          // rtr: bit 30 only
                linuxFrame.can_id & CAN_EFF_FLAG,          // ide: bit 31 only,
                can::protocol::frame::data::EDL::CC_FRAME, // edl: libsockcanpp only supports CC frame
                linuxFrame.len,                            // dlc
                &linuxFrame.data,                          // data
                8                                          // data size
            );
        }

        return std::nullopt;
    }

    CANBus::~CANBus() = default;
}