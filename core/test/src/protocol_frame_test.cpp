#include "protocol_frame_test.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gmock-global/gmock-global.h>

using namespace can::protocol::frame;

using namespace testing;

MOCK_GLOBAL_FUNC1(create_mock, frame_res(frame_raw_t));

TEST_P(ProtocolFrameTest, create)
{
    create_input input = GetParam();

    // expect create to be called once
    EXPECT_GLOBAL_CALL(create_mock, create_mock(input.frame_raw)).Times(input.create_called_times);

    // when create is called, delegate (exec) the real method
    ON_GLOBAL_CALL(create_mock, create_mock(input.frame_raw)).WillByDefault(can::protocol::frame::create);

    frame_res res = create_mock(input.frame_raw);

    if (input.should_have_value)
    {
        EXPECT_TRUE(res.has_value());
        frame_t frame = res.value();

        // Assertations

        if (input.should_dlc_match_actual_data_size)
        {
            ASSERT_EQ(input.frame_raw.dlc, frame._actualdataSize);
        }

        if (input.should_raw_match_response)
        {
            // TODO: check extended too!
            ASSERT_EQ(input.frame_raw.id, frame.id.base);
            // frame.id.extended

            ASSERT_EQ(input.frame_raw.rtr, frame.rtr);
            ASSERT_EQ(input.frame_raw.ide, frame.ide);
            ASSERT_EQ(input.frame_raw.edl, frame.edl);

            ASSERT_EQ(input.frame_raw.dlc, frame.dlc.dlc);
            ASSERT_EQ(input.frame_raw.data_size, frame._maxDataSize);
        }
        // char *res_data_ptr = (char *)&(res.value().data[0]);
        // EXPECT_STREQ(data, res_data_ptr);
    }
    else
    {
        EXPECT_FALSE(res.has_value());
    }
}