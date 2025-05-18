#include "core/isotp/error/code/code.h"

using can::isotp::error::condition::FrameCondition;

namespace can::isotp::error::code
{
    std::unordered_map<int, code_property_t> code_messages = {
        {ConsecutiveFrameError::LINK_STATE_MISMATCH,
         {"link state mismatch", FrameCondition::ISOTP_FRAME_IGNORED}},

        {ConsecutiveFrameError::PKT_SEQUENCE_NUMBER_MISMATCH,
         {"sequence number mismatch", FrameCondition::ISOTP_FRAME_IGNORED}},

        {ConsecutiveFrameError::PKT_PAYLOAD_TOO_LONG,
         {"payload too long", FrameCondition::ISOTP_FRAME_INVALID}},

        {FirstFrameError::PKT_UNEXPECTED_SIGNALLING,
         {"unexpected signalling",
          FrameCondition::ISOTP_FRAME_INVALID}},

        {FrameHandleError::NO_HANDLER_FOR_TYPE,
         {"no frame handler for recieved type", FrameCondition::ISOTP_FRAME_INVALID}},

        {LinkManagerError::IGNORED_ID_NOT_REGISTERED,
         {"frame ignored as ID was not registered", FrameCondition::ISOTP_FRAME_IGNORED}},

        {SingleFrameError::PKT_CC_IGNORED_DL_RESERVED,
         {"frame had reserved data length set", FrameCondition::ISOTP_FRAME_IGNORED}},

        {SingleFrameError::PKT_CC_INVALID_DL_WHILE_EXTENDED,
         {"invalid data length for extended frame", FrameCondition::ISOTP_FRAME_INVALID}},

        {SingleFrameError::PKT_CC_INVALID_DL,
         {"invalid data length", FrameCondition::ISOTP_FRAME_INVALID}},

        {SingleFrameError::PKT_CC_PAYLOAD_LEN_TOO_SMALL,
         {"payload length too small", FrameCondition::ISOTP_FRAME_INVALID}},

        {SingleFrameError::PKT_FD_IGNORED_FL_LOWER_ZERO,
         {"spec-ignored FD frame", FrameCondition::ISOTP_FRAME_IGNORED}},

        {SingleFrameError::PKT_UNKNOWN,
         {"unknown frame", FrameCondition::ISOTP_FRAME_UNKNOWN}},

    };
};

//{Success::SUCCESS},
/**
{ConsecutiveFrameError::LINK_STATE_MISMATCH, {"Link state mismatch", can::isotp::error::condition::FrameCondition::ISOTP_FRAME_IGNORED}},
{ConsecutiveFrameError::PKT_SEQUENCE_NUMBER_MISMATCH, {"Sequence number mismatch", can::isotp::error::condition::FrameCondition::ISOTP_FRAME_IGNORED}},
{
    ConsecutiveFrameError::PKT_PAYLOAD_TOO_LONG,
    {"Payload too long",
     can::isotp::error::condition::FrameCondition::ISOTP_FRAME_INVALID},
},

{FirstFrameError::PKT_UNEXPECTED_SIGNALLING, {"Unexpected signalling.", can::isotp::error::condition::FrameCondition::ISOTP_FRAME_INVALID}},

{FrameHandleError::NO_HANDLER_FOR_TYPE,
 {"No handler for type", can::isotp::error::condition::FrameCondition::ISOTP_FRAME_IGNORED}},

{LinkManagerError::IGNORED_ID_NOT_REGISTERED, {"Packet was ignored.", can::isotp::error::condition::FrameCondition::ISOTP_FRAME_IGNORED}},
*/