#include "can/protocol/isotp/error/common/category/isotp.h"

#include <iostream>

namespace can::protocol::isotp::error::common::category
{
    namespace impl
    {

        const char *ISOTP::name() const noexcept
        {
            return "libcan.isotp";
        };
    };

    boost::system::error_category const &isotp_category()
    {
        static const impl::ISOTP instance;
        return instance;
    }
};
