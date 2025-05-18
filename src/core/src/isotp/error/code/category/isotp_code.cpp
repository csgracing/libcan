#include "core/isotp/error/code/category/isotp_code.h"

#include <iostream>

#include <fmt/core.h>

#include "core/isotp/error/common/overload.h"
#include "core/isotp/error/code/code.h"

#include "core/isotp/error/condition/frame_condition.h"

using can::isotp::error::common::overloaded;
using can::isotp::error::condition::FrameCondition;

namespace can::isotp::error::code::category
{
    namespace impl
    {

        const char *ISOTPCodeCategory::name() const noexcept
        {
            return "libcan.isotp.code";
        };

        char const *ISOTPCodeCategory::message(int ev, char *buffer, std::size_t len) const noexcept
        {

            if (code_messages.find(ev) != code_messages.end())
            {
                return code_messages.at(ev).message;
            }
            else
            {

                std::snprintf(buffer, len, "Unknown isotp code %d", ev);
                return buffer;
            }
        };

        boost::system::error_condition ISOTPCodeCategory::default_error_condition(int ev) const noexcept
        {

            if (code_messages.find(ev) != code_messages.end())
            {
                return code_messages.at(ev).cond;
            }
            else
            {

                return boost::system::error_condition(ev, *this);
            }
        };
    };

    boost::system::error_category const &isotp_code_category()
    {
        static const impl::ISOTPCodeCategory instance;
        return instance;
    };
}
