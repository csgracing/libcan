#ifndef PROVIDERS_BASE_H_
#define PROVIDERS_BASE_H_

#include <type_traits>
#include <optional> // std::optional

#include "concurrentqueue.h"

#include "core/protocol/frame/frame.h"

#define BITS_IN_KB 1000

namespace can::providers::base
{

    enum class Bitrate
    {
    };

    typedef std::underlying_type<Bitrate>::type bitrate_enum_t;

    enum class Clock
    {
    };

    typedef std::underlying_type<Clock>::type clock_enum_t;

    struct Options
    {
        // We need this or any other virtual member to make Base polymorphic
        // (so we can use dynamic_cast or boost casting)
        // https://stackoverflow.com/a/36739219 (polymorphism)
        // https://www.boost.org/doc/libs/1_47_0/libs/conversion/cast.htm#Polymorphic_cast
        virtual ~Options() {}
    };

    class CANBus
    {
    private:
        moodycamel::ConcurrentQueue<can::protocol::frame::frame_t> queue;

    public:
        CANBus(std::optional<bitrate_enum_t> b, Options *o);
        virtual ~CANBus(); // desructor

        // derived classes must provide an implementation (=0)
        // <https://stackoverflow.com/a/2089238>
        virtual can::protocol::frame::frame_res readMessage() = 0;
        virtual bool hasMessage() = 0;

        can::protocol::frame::frame_res createFrame(can::protocol::frame::identifier id, uint8_t *data, uint8_t data_length);

        void handleQueue();
        bool enqueue(can::protocol::frame::frame_t frame);

        virtual bool sendMessage(can::protocol::frame::frame_t frame) = 0;
    };
};

#endif /* PROVIDERS_BASE_H_ */