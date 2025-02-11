#include "gtest/gtest.h"

#include "protocol_frame_test_input.h"
#include "protocol_frame_test.h"

// Options *o = new Options();

#include <list>

std::list<create_input> inputs;

void addInput(std::string testcase_display_name, std::string str, std::string expected_str, uint32_t id, bool rtr, bool ide, bool edl, uint8_t max_data_size, uint8_t create_called_times, bool should_have_value, bool should_raw_match_response, bool should_dlc_match_actual_data_size)
{
    inputs.push_back({
        testcase_display_name,
        {
            id,
            rtr,
            ide,
            edl,
            (uint8_t)(str.size() + 1), // str.size() // str.length() does not include string termination
            str.data(),
            max_data_size,
        },
        create_called_times,
        should_have_value,
        should_raw_match_response,
        should_dlc_match_actual_data_size,
        expected_str,
    });
}

int main(int argc, char **argv)
{
    // Valid CAN CC frame
    addInput(
        "valid_cc",
        "Test",
        "Test",
        0x1,
        false,
        false,
        false,
        8,
        1,
        true,
        true,
        true);

    // Valid CAN CC (extended ID) frame
    addInput(
        "valid_cc_ext",
        "Test",
        "Test",
        0x12345678,
        false,
        true,
        false,
        8,
        1,
        true,
        true,
        true);

    // Valid CAN CC frame (edge-case, dlc > 8 so will be truncated as per spec)
    addInput(
        "valid_cc_edgecase_dlc_above_8",
        "TestTestTest",
        "TestTest",
        0x1,
        false,
        false,
        false,
        8,
        1,
        true,
        false,
        false);

    // Invalid CAN FD frame (FD frames cannot be remote frames)
    addInput(
        "invalid_fd_remote_frame",
        "Test",
        "Test",
        0x1,
        true,
        false,
        true,
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