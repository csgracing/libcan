#ifndef CONDITION_FRAME_H_
#define CONDITION_FRAME_H_

#include <boost/system/is_error_condition_enum.hpp>
#include <boost/system/error_condition.hpp>

#include "core/isotp/error/condition/category/isotp_condition.h"

namespace can::isotp::error::condition
{
    enum FrameCondition
    {
        ISOTP_FRAME_IGNORED = 1,
        ISOTP_FRAME_INVALID,
        ISOTP_FRAME_UNKNOWN,

    };

    inline boost::system::error_condition make_error_condition(FrameCondition e)
    {
        return boost::system::error_condition(static_cast<int>(e), category::isotp_condition_category());
    }
};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_condition_enum<::can::isotp::error::condition::FrameCondition> : std::true_type
        {
        };
    };
};

#endif /* CONDITION_FRAME_H_ */