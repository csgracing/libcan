#include "core/isotp/error/category/isotp.h"

#include <iostream>

namespace can::isotp::error::category
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
