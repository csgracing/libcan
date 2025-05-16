#ifndef ERROR_FIRST_FRAME
#define ERROR_FIRST_FRAME

#include <boost/system/is_error_code_enum.hpp>
#include <boost/system/error_code.hpp>

#include "core/isotp/error/code/category/isotp_code.h"

namespace can::isotp::error::code
{
    enum FirstFrameError
    {
        PKT_UNEXPECTED_SIGNALLING,
    };

    inline boost::system::error_code make_error_code(FirstFrameError e)
    {
        return boost::system::error_code(static_cast<int>(e), category::isotp_code_category());
    }
};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_code_enum<::can::isotp::error::code::FirstFrameError> : std::true_type
        {
        };
    };
};

#endif /* ERROR_FIRST_FRAME */