#include "gtest/gtest.h"

#include "protocol_frame_test_input.h"
#include "protocol_frame_test.h"
#include "sequence_number_test.h"

// Options *o = new Options();

#include <list>

std::list<create_input> inputs;

void addInput(
    std::string testcase_display_name,
    char *data,
    uint8_t dlc,
    uint8_t size_bytes,
    char *expected_data,
    uint8_t expected_data_size,
    uint32_t id,
    bool rtr,
    bool ide,
    bool edl,
    uint8_t size_dlc_max,
    uint8_t create_called_times,
    bool should_have_value,
    bool should_raw_match_response,
    bool should_dlc_match_actual_data_size)
{

    inputs.push_back({
        testcase_display_name,
        {
            id,
            rtr,
            ide,
            edl,
            dlc,
            data,
            size_dlc_max,
            size_bytes,
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

    addInput("valid_cc",
             data8, // input data
             8,     // input dlc
             8,     // input byte size
             data8, // expected data
             8,     // expected data byte size
             0x1,   // can id
             false, // rtr
             false, // ide
             false, // edl
             15,    // max dlc size for proto (15 for can FD)
             1,     // create should be called x times
             true,  // should have value
             true,  // should raw match response
             true); // should dlc match actual data size

    addInput("valid_cc_ext",
             data8,      // input data
             8,          // input dlc
             8,          // input byte size
             data8,      // expected data
             8,          // expected data byte size
             0x12345678, // can id
             false,      // rtr
             true,       // ide
             false,      // edl
             8,          // max dlc size for proto (15 for can FD)
             1,          // create should be called x times
             true,       // should have value
             true,       // should raw match response
             true);      // should dlc match actual data size

    // Valid CAN CC frame (edge-case, dlc > 8 so will be truncated as per spec)
    addInput("valid_cc_edgecase_dlc_above_8",
             data15, // input data
             15,     // input dlc
             8,      // input byte size
             data8,  // expected data
             8,      // expected data byte size
             0x1,    // can id
             false,  // rtr
             false,  // ide
             false,  // edl
             8,      // max dlc size for proto (15 for can FD)
             1,      // create should be called x times
             true,   // should have value
             true,   // should raw match response
             true);  // should dlc match actual data size

    // Invalid CAN FD frame (FD frames cannot be remote frames)
    addInput("invalid_fd_remote_frame",
             data8,  // input data
             8,      // input dlc
             8,      // input byte size
             data8,  // expected data
             8,      // expected data byte size
             0x1,    // can id
             true,   // rtr
             false,  // ide
             true,   // edl
             8,      // max dlc size for proto (15 for can FD)
             1,      // create should be called x times
             false,  // should have value
             false,  // should raw match response
             false); // should dlc match actual data size

    addInput("invalid_cc_dlc_overflowed",
             data8,   // input data
             0b10000, // input dlc
             128,     // input byte size
             data8,   // expected data
             8,       // expected data byte size
             0x1,     // can id
             false,   // rtr
             false,   // ide
             false,   // edl
             15,      // max dlc size for proto (15 for can FD)
             1,       // create should be called x times
             false,   // should have value
             false,   // should raw match response
             false);  // should dlc match actual data size

    addInput("invalid_cc_ext_id_no_ide_bit_set",
             data8,      // input data
             8,          // input dlc
             8,          // input byte size
             data8,      // expected data
             8,          // expected data byte size
             0x12345678, // can id
             false,      // rtr
             false,      // ide
             false,      // edl
             15,         // max dlc size for proto (15 for can FD)
             1,          // create should be called x times
             false,      // should have value
             false,      // should raw match response
             false);     // should dlc match actual data size

    addInput("valid_fd",
             data32, // input data
             13,     // input dlc
             32,     // input byte size
             data32, // expected data
             32,     // expected data byte size
             0x1,    // can id
             false,  // rtr
             false,  // ide
             true,   // edl
             15,     // max dlc size for proto (15 for can FD)
             1,      // create should be called x times
             true,   // should have value
             true,   // should raw match response
             true);  // should dlc match actual data size

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