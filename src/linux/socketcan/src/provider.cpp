#include <stdio.h>

#include "linux/socketcan/provider.h"

#include "core/logger.h"

#include <boost/polymorphic_cast.hpp> // boost::conversion

using std::chrono::milliseconds;

using sockcanpp::CanMessage;

namespace can::providers::os::socketcan
{
    CANBus::CANBus(std::optional<base::bitrate_enum_t> b, base::Options *o) : base::CANBus(b, o)
    {
        this->op = boost::polymorphic_downcast<Options *>(o);

        if (!this->op->filterMask.has_value())
            LIBCAN_LOG_DEBUG("provider", "Using default param for filterMask");

        if (!this->op->defaultSenderId.has_value())
            LIBCAN_LOG_DEBUG("provider", "Using default param for defaultSenderId");

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
        if (this->hasMessage())
        {
            // There is a message available
            CanMessage recvMessage = this->driver->readMessage();

            // Get linux internal can_frame
            can_frame linuxFrame = recvMessage.getRawFrame();

            can::protocol::frame::frame_raw_t raw_frame = {
                linuxFrame.can_id & CAN_ERR_MASK,          // id: bits 0-28 (shift out 29,30,31)
                (bool)(linuxFrame.can_id & CAN_RTR_FLAG),  // rtr: bit 30 only
                (bool)(linuxFrame.can_id & CAN_EFF_FLAG),  // ide: bit 31 only,
                can::protocol::frame::data::EDL::CC_FRAME, // edl: libsockcanpp only supports CC frame
                linuxFrame.len,                            // dlc
                &linuxFrame.data,                          // data
                8                                          // data size
            };

            return can::protocol::frame::create(raw_frame);
        }

        return std::nullopt;
    }

    bool CANBus::hasMessage()
    {
        // call waitForMessages to update fdsAvailable (has packet) but don't block (0ms timeout)
        return this->driver->waitForMessages(milliseconds(0));
    }

    bool CANBus::sendMessage(can::protocol::frame::frame_t frame)
    {
        // todo ID should contain flags...
        CanId id(frame.id.combined());

        can_frame rawFrame;
        rawFrame.can_id = frame.id.combined();
        rawFrame.can_dlc = frame.dlc.to_ulong();
        memcpy(rawFrame.data, &frame.data, frame._bsize.to_ulong());
        CanMessage msg(rawFrame);

        // if trace logging enabled, log what we are sending
        LIBCAN_LOG_TRACE_BUF("provider", frame.data, frame._bsize.to_ulong(), "Sending data: {}");

        auto sentByteCount = driver->sendMessage(msg);

        LIBCAN_LOG_DEBUG("provider", fmt::format("Sent bytes: {}", sentByteCount));

        return sentByteCount != 0;
    }

    CANBus::~CANBus() = default;
}