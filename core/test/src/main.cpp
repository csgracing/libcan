#include "gtest/gtest.h"

#include "protocol_frame_test_input.h"
#include "protocol_frame_test.h"

// Options *o = new Options();

#include <list>

std::list<create_input> inputs;

int main(int argc, char **argv)
{

    char *data = (char *)calloc(8, sizeof(uint8_t));

    strcpy(data, "Test");

    // init inputs
    inputs.push_back({
        {
            0x1,   // id
            false, // rtr
            false, // ide
            false, // edl
            8,     // dlc
            data,  // data
            8,     // data size
        },
        1,    // create_called_times
        true, // should_have_value
        true, // should_raw_match_response
        true  // should_dlc_match_actual_data_size;
    });

    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}

INSTANTIATE_TEST_SUITE_P(Example, ProtocolFrameTest, testing::ValuesIn(inputs));