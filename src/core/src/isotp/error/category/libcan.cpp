#include "core/isotp/error/category/libcan.h"

namespace can::isotp::error::category
{
    namespace impl
    {

        const char *LibCAN::name() const noexcept
        {
            return "libcan";
        };

        std::string LibCAN::message(int ev) const
        {
            char buffer[64];
            return this->message(ev, buffer, sizeof(buffer));
        };

        char const *LibCAN::message(int ev, char *buffer, std::size_t len) const noexcept
        {
            std::snprintf(buffer, len, "Unknown libcan error %d", ev);
            return buffer;
        }
    };

    boost::system::error_category const &libcan_category()
    {
        static const impl::LibCAN instance;
        return instance;
    }
};
