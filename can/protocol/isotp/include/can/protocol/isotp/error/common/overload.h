#ifndef COMMON_OVERLOAD_H_
#define COMMON_OVERLOAD_H_

namespace can::isotp::error::common
{
    // std visit "switch" style
    // https://stackoverflow.com/a/63483353

    template <class... Ts>
    struct overloaded : Ts...
    {
        using Ts::operator()...;
    };

    template <class... Ts>
    overloaded(Ts...) -> overloaded<Ts...>;
};

#endif /* COMMON_OVERLOAD_H_ */