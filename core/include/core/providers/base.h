#ifndef PROVIDERS_BASE_H_
#define PROVIDERS_BASE_H_

#include <type_traits>

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
    };

    typedef std::underlying_type<Options> options_t;

    class CANBus
    {
    public:
        CANBus(bitrate_enum_t b, options_t o);
        virtual ~CANBus(); // desructor
    };
};

#endif /* PROVIDERS_BASE_H_ */