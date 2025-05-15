#ifndef ERROR_FRAME_H_
#define ERROR_FRAME_H_

#include <boost/system/is_error_code_enum.hpp>
#include <boost/system/error_code.hpp>

#include "core/isotp/error/category/isotp.h"

namespace can::isotp::error
{
    enum class FrameHandleError
    {
        SUCCESS = 0,
        NO_HANDLER_FOR_TYPE,
    };

    inline boost::system::error_code make_error_code(FrameHandleError e)
    {
        return boost::system::error_code(static_cast<int>(e), category::libcan_category());
    }
};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_code_enum<::can::isotp::error::FrameHandleError> : std::true_type
        {
        };
    };
};

#endif /* ERROR_FRAME_H_ */