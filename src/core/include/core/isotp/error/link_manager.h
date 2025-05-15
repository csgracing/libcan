#ifndef ERROR_LINK_MANAGER_H_
#define ERROR_LINK_MANAGER_H_

#include <boost/system/is_error_code_enum.hpp>
#include <boost/system/error_code.hpp>

#include "core/isotp/error/category/isotp.h"

namespace can::isotp::error
{
    enum class LinkManagerError
    {
        SUCCESS = 0,
        IGNORED_ID_NOT_REGISTERED,
    };

    inline boost::system::error_code make_error_code(LinkManagerError e)
    {
        return boost::system::error_code(static_cast<int>(e), category::isotp_category());
    }
};

namespace boost
{
    namespace system
    {
        template <>
        struct is_error_code_enum<::can::isotp::error::LinkManagerError> : std::true_type
        {
        };
    };
};

#endif /* ERROR_LINK_MANAGER_H_ */