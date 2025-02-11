#include "gtest/gtest.h"

#include "protocol_frame_test_input.h"
#include "protocol_frame_test.h"

// Options *o = new Options();

#include <list>

std::list<create_input> inputs;

void addInput(std::string testcase_display_name, std::string str, uint32_t id, bool rtr, bool ide, bool edl, uint8_t dlc, uint8_t max_data_size, uint8_t create_called_times, bool should_have_value, bool should_raw_match_response, bool should_dlc_match_actual_data_size)
{

    char *data = (char *)str.c_str();

    inputs.push_back({
        testcase_display_name,
        {
            id,
            rtr,
            ide,
            edl,
            dlc,
            data,
            max_data_size,
        },
        create_called_times,
        should_have_value,
        should_raw_match_response,
        should_dlc_match_actual_data_size,
    });
}

int main(int argc, char **argv)
{
    // Valid CAN CC frame
    addInput(
        "valid_cc",
        "Test",
        0x1,
        false,
        false,
        false,
        8,
        8,
        1,
        true,
        true,
        true);

    // Valid CAN CC (extended ID) frame
    addInput(
        "valid_cc_ext",
        "Test",
        0x12345678,
        false,
        true,
        false,
        8,
        8,
        1,
        true,
        true,
        true);

    // Invalid CAN FD frame (FD frames cannot be remote frames)
    addInput(
        "invalid_fd_remote_frame",
        "Test",
        0x1,
        true,
        false,
        true,
        8,
        8,
        1,
        false,
        false,
        false);

    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}

INSTANTIATE_TEST_SUITE_P(
    Suite, // prefix
    ProtocolFrameTest,
    testing::ValuesIn(inputs),
    // set name based on value in param
    // https://github.com/google/googletest/blob/main/docs/advanced.md#specifying-names-for-value-parameterized-test-parameters
    [](const testing::TestParamInfo<ProtocolFrameTest::ParamType> &info)
    {
        return info.param.test_case_display_name;
    });