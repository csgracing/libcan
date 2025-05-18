#ifndef ERROR_SINGLE_FRAME
#define ERROR_SINGLE_FRAME

#include <boost/system/is_error_code_enum.hpp>
#include <boost/system/error_code.hpp>

#include "core/isotp/error/code/category/isotp_code.h"

namespace can::isotp::error::code
{
    enum SingleFrameError
    {
        PKT_CC_IGNORED_DL_RESERVED = 50,
        PKT_CC_INVALID_DL_WHILE_EXTENDED,
        PKT_CC_INVALID_DL,
        PKT_CC_PAYLOAD_LEN_TOO_SMALL,
        PKT_FD_IGNORED_FL_LOWER_ZERO,
        PKT_UNKNOWN,
    };

    inline boost::system::error_code make_error_code(SingleFrameError e)
    {
        return boost::system::error_code(static_cast<int>(e), category::isotp_code_category());
    }

};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_code_enum<::can::isotp::error::code::SingleFrameError> : std::true_type
        {
        };
    };
};

#endif /* ERROR_SINGLE_FRAME */