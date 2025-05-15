#ifndef CATEGORY_LIBCAN_H_
#define CATEGORY_LIBCAN_H_

#include <string> // string, size_t

#include <boost/system/error_category.hpp>

namespace can::isotp::error::category
{
    namespace impl
    {
        class LibCAN : public boost::system::error_category
        {
        public:
            const char *name() const noexcept;
            std::string message(int ev) const;
            char const *message(int ev, char *buffer, std::size_t len) const noexcept;
        };
    };

    boost::system::error_category const &libcan_category();
};

#endif /* CATEGORY_LIBCAN_H_ */