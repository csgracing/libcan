#include "core/isotp/error/condition/category/isotp_condition.h"

#include <iostream>

#include <fmt/core.h>

#include "core/isotp/error/common/overload.h"
#include "core/isotp/error/condition/condition.h"
#include "core/isotp/error/condition/frame_condition.h"

using can::isotp::error::common::overloaded;
using can::isotp::error::condition::Condition;
using can::isotp::error::condition::FrameCondition;

namespace can::isotp::error::condition::category
{
    namespace impl
    {

        const char *ISOTPConditionCategory::name() const noexcept
        {
            return "libcan.isotp.condition";
        };

        char const *ISOTPConditionCategory::message(int ev, char *buffer, std::size_t len) const noexcept
        {
            // -> std::string inferred, just added for clarity
            auto msg = [&ev]() -> std::string
            {
                switch (ev)
                {
                case FrameCondition::ISOTP_FRAME_IGNORED:
                    return std::string("ISO-TP frame was ignored");
                case FrameCondition::ISOTP_FRAME_INVALID:
                    return std::string("ISO-TP frame was invalid");
                case FrameCondition::ISOTP_FRAME_UNKNOWN:
                    return std::string("ISO-TP frame could not be parsed");
                default:
                    return fmt::format("Unknown isotp condition {}", ev);
                };
            };

            std::snprintf(buffer, len, msg().c_str());
            return buffer;
        };
    };

    boost::system::error_category const &isotp_condition_category()
    {
        static const impl::ISOTPConditionCategory instance;
        return instance;
    }
};
