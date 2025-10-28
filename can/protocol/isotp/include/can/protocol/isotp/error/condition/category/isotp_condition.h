#ifndef CATEGORY_ISOTP_CONDITION_H_
#define CATEGORY_ISOTP_CONDITION_H_

#include "can/protocol/isotp/error/common/category/isotp.h"

namespace can::protocol::isotp::error::condition::category
{
    namespace impl
    {
        class ISOTPConditionCategory : public can::protocol::isotp::error::common::category::impl::ISOTP
        {
        public:
            const char *name() const noexcept override;

            char const *message(int ev, char *buffer, std::size_t len) const noexcept override;
        };
    };

    boost::system::error_category const &isotp_condition_category();
};

#endif /* CATEGORY_ISOTP_CONDITION_H_ */