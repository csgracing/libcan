#ifndef ERROR_FRAME_H_
#define ERROR_FRAME_H_

#include <boost/system/is_error_code_enum.hpp>
#include <boost/system/error_code.hpp>

#include "core/isotp/error/code/category/isotp_code.h"

namespace can::isotp::error::code
{
    enum FrameHandleError
    {
        NO_HANDLER_FOR_TYPE = 30,
    };

    inline boost::system::error_code make_error_code(FrameHandleError e)
    {
        return boost::system::error_code(static_cast<int>(e), category::isotp_code_category());
    }
};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_code_enum<::can::isotp::error::code::FrameHandleError> : std::true_type
        {
        };
    };
};

#endif /* ERROR_FRAME_H_ */