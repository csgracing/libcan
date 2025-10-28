#ifndef CODE_CODE_H_
#define CODE_CODE_H_

#include <variant>

#include <boost/system/error_condition.hpp>

#include "can/protocol/isotp/error/condition/frame_condition.h"

#include "can/protocol/isotp/error/code/consecutive_frame.h"
#include "can/protocol/isotp/error/code/first_frame.h"
#include "can/protocol/isotp/error/code/frame_handle.h"
#include "can/protocol/isotp/error/code/link_manager.h"
#include "can/protocol/isotp/error/code/single_frame.h"

namespace can::protocol::isotp::error::code
{
    enum Success
    {
        SUCCESS = 0,
    };
    struct Code
    {
        using enum Success;
        using enum ConsecutiveFrameError;
        using enum FirstFrameError;
        using enum FrameHandleError;
        using enum LinkManagerError;
        using enum SingleFrameError;
    };

    typedef struct
    {
        const char *message;
        boost::system::error_condition cond;
    } code_property_t;

    extern std::unordered_map<int, code_property_t> code_messages;
};

#endif /* CODE_CODE_H_ */