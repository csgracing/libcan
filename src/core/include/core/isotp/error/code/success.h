#ifndef CODE_SUCCESS_H_
#define CODE_SUCCESS_H_

#include <boost/system/is_error_code_enum.hpp>
#include <boost/system/error_code.hpp>

#include "core/isotp/error/code/category/isotp_code.h"

namespace can::isotp::error::code
{
    enum Success
    {
        SUCCESS = 0,
    };

    inline boost::system::error_code make_error_code(Success e)
    {
        return boost::system::error_code(static_cast<int>(e), category::isotp_code_category());
    }

};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_code_enum<::can::isotp::error::code::Success> : std::true_type
        {
        };
    };
};

#endif /* CODE_SUCCESS_H_ */