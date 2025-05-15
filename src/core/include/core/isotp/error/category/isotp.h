#ifndef CATEGORY_ISOTP_H_
#define CATEGORY_ISOTP_H_

#include "core/isotp/error/category/libcan.h"

namespace can::isotp::error::category
{
    namespace impl
    {
        class ISOTP : public LibCAN
        {
        public:
            const char *name() const noexcept override;
        };
    };

    boost::system::error_category const &isotp_category();
};

#endif /* CATEGORY_ISOTP_H_ */