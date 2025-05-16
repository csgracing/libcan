#ifndef ERROR_CONSECUTIVE_FRAME_H_
#define ERROR_CONSECUTIVE_FRAME_H_

#include <boost/system/is_error_code_enum.hpp>
#include <boost/system/error_code.hpp>

#include "core/isotp/error/code/category/isotp_code.h"

namespace can::isotp::error::code
{
    enum ConsecutiveFrameError
    {
        LINK_STATE_MISMATCH = 1,
        PKT_SEQUENCE_NUMBER_MISMATCH,
        PKT_PAYLOAD_TOO_LONG,
    };

    inline boost::system::error_code make_error_code(ConsecutiveFrameError e)
    {
        return boost::system::error_code(static_cast<int>(e), category::isotp_code_category());
    }
};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_code_enum<::can::isotp::error::code::ConsecutiveFrameError> : std::true_type
        {
        };
    };
};

#endif /* ERROR_CONSECUTIVE_FRAME_H_ */