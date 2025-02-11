#include "gtest/gtest.h"

#include "protocol_frame_test_input.h"
#include "protocol_frame_test.h"

// Options *o = new Options();

#include <list>

std::list<create_input> inputs;

void addInput(std::string testcase_display_name, char *data, uint8_t data_size, char *expected_data, uint8_t expected_data_size, uint32_t id, bool rtr, bool ide, bool edl, uint8_t max_data_size, uint8_t create_called_times, bool should_have_value, bool should_raw_match_response, bool should_dlc_match_actual_data_size)
{

    inputs.push_back({
        testcase_display_name,
        {
            id,
            rtr,
            ide,
            edl,
            data_size,
            data,
            max_data_size,
        },
        create_called_times,
        should_have_value,
        should_raw_match_response,
        should_dlc_match_actual_data_size,
        expected_data,
        expected_data_size,
    });
}

int main(int argc, char **argv)
{
    // TODO: dlc >15 will overflow, need to check for this!
    char *data8 = (char *)calloc(8, sizeof(uint8_t));
    char *data15 = (char *)calloc(15, sizeof(uint8_t));
    char *data32 = (char *)calloc(32, sizeof(uint8_t));

    memset(data8, 0xf0, 8);
    memset(data15, 0xf1, 15);
    memset(data15, 0xf0, 8);

    // Valid CAN CC frame
    addInput(
        "valid_cc",
        data8, 8,
        data8, 8,
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
        data8, 8,
        data8, 8,
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
        data15, 15,
        data8, 8,
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
        data8, 8,
        data8, 8,
        0x1,
        true,
        false,
        true,
        8,
        1,
        false,
        false,
        false);

    addInput("invalid_cc_dlc_overflowed",
             data8, 0b10000,
             data8, 8,
             0x1,
             false,
             false,
             false,
             8,
             1,
             false,
             false,
             false);

    addInput("invalid_cc_ext_id_no_ide_bit_set",
             data8, 8,
             data8, 8,
             0x12345678,
             false,
             false,
             false,
             8,
             1,
             false,
             false,
             false);

    addInput("valid_fd",
             data32, 13, // 32b
             data32, 13, // 32b
             0x1,
             false,
             false,
             true,
             64,
             1,
             true,
             true,
             true);

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