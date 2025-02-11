#include "protocol_frame_test.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gmock-global/gmock-global.h>

using namespace can::protocol::frame;

using namespace testing;

MOCK_GLOBAL_FUNC1(create_mock, frame_res(frame_raw_t));

std::shared_ptr<frame_res> ProtocolFrameTest::m_res = NULL;

void ProtocolFrameTest::SetUp()
{
    create_input input = GetParam();

    // expect create to be called (given) number of times
    EXPECT_GLOBAL_CALL(create_mock, create_mock(input.frame_raw)).Times(input.create_called_times);

    // when create is called, delegate (exec) the real method
    ON_GLOBAL_CALL(create_mock, create_mock(input.frame_raw)).WillByDefault(can::protocol::frame::create);

    frame_res res_local = create_mock(input.frame_raw);

    m_res = std::make_shared<frame_res>(res_local);
};

void ProtocolFrameTest::TearDown()
{
    m_res.reset();
};

TEST_P(ProtocolFrameTest, has_value)
{
    create_input input = GetParam();

    frame_res *res = m_res.get();

    EXPECT_EQ(input.should_have_value, res->has_value());
};

TEST_P(ProtocolFrameTest, raw_matches_response)
{
    create_input input = GetParam();

    if (!input.should_raw_match_response || !input.should_have_value)
    {
        GTEST_SKIP();
    }
    else
    {
        frame_res *res = m_res.get();
        frame_t frame = res->value();

        // TODO: check extended too!
        // ASSERT_EQ(input.frame_raw.id, frame.id.base);
        ASSERT_EQ(input.frame_raw.id, frame.id.combined());
        // frame.id.extended

        ASSERT_EQ(input.frame_raw.rtr, frame.rtr);
        ASSERT_EQ(input.frame_raw.ide, frame.ide);
        ASSERT_EQ(input.frame_raw.edl, frame.edl);

        ASSERT_EQ(input.frame_raw.dlc, frame.dlc.dlc);
        ASSERT_EQ(input.frame_raw.data_size, frame._maxDataSize);
    }
};

TEST_P(ProtocolFrameTest, data_expected_cc)
{
    create_input input = GetParam();
    if (!input.should_have_value)
    {
        GTEST_SKIP();
    }
    else
    {
        frame_res *res = m_res.get();
        frame_t frame = res->value();

        if (frame._type & FrameType::CC)
        {

            char *res_data_ptr = (char *)&(frame.data[0]);
            EXPECT_STREQ(input.expected_str.c_str(), res_data_ptr);
        }
        else
        {
            GTEST_SKIP_("Frame was not a CAN CC frame.");
        }
    };
};

TEST_P(ProtocolFrameTest, dlc_matches_actual_data_size)
{
    create_input input = GetParam();
    if (!input.should_dlc_match_actual_data_size || !input.should_have_value)
    {
        GTEST_SKIP();
    }
    else
    {
        frame_res *res = m_res.get();
        frame_t frame = res->value();

        ASSERT_EQ(input.frame_raw.dlc, frame._actualdataSize);
    }
};