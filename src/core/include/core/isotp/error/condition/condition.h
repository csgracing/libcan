#ifndef CONDITION_CONDITION_H_
#define CONDITION_CONDITION_H_

#include <variant>

#include "core/isotp/error/condition/frame_condition.h"

namespace can::isotp::error::condition
{
    struct Condition
    {
        using enum FrameCondition;
    };
};

#endif /* CONDITION_CONDITION_H_ */