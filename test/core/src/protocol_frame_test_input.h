#ifndef SRC_PROTOCOL_FRAME_TEST_INPUT_H_
#define SRC_PROTOCOL_FRAME_TEST_INPUT_H_

#include "core/protocol/frame/frame.h"

// create TEST_P input struct

typedef struct
{
    uint8_t expected_id_base;
    uint8_t expected_id_extended;
    can::protocol::frame::data::RTR expected_rtr;
    can::protocol::frame::data::IDE expected_ide;
    can::protocol::frame::data::EDL expected_edl;
    uint8_t expected_dlc;
    uint8_t expected_max_data_size;
    can::protocol::frame::FrameType expected_type;
} create_input_expected;

typedef struct
{
    std::string test_case_display_name;
    can::protocol::frame::frame_raw_t frame_raw;
    uint8_t create_called_times;
    bool should_have_value;
    bool should_raw_match_response;
    bool should_dlc_match_actual_data_size;
    char *expected_data;
    uint8_t expected_data_size;

    std::optional<create_input_expected> expected;
} create_input;

#endif /* SRC_PROTOCOL_FRAME_TEST_INPUT_H_ */