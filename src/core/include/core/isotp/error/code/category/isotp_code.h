#ifndef CATEGORY_ISOTP_CODE_H_
#define CATEGORY_ISOTP_CODE_H_

#include "core/isotp/error/common/category/isotp.h"

namespace can::isotp::error::code::category
{
    namespace impl
    {
        class ISOTPCodeCategory : public can::isotp::error::common::category::impl::ISOTP
        {
        public:
            const char *name() const noexcept override;

            char const *message(int ev, char *buffer, std::size_t len) const noexcept override;

            boost::system::error_condition default_error_condition(int ev) const noexcept;
        };
    };

    boost::system::error_category const &isotp_code_category();
};

#endif /* CATEGORY_ISOTP_CODE_H_ */