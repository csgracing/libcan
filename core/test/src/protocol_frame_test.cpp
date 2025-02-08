#include "protocol_frame_test.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gmock-global/gmock-global.h>

using namespace can::protocol::frame;

using namespace testing;

MOCK_GLOBAL_FUNC7(create_mock, frame_res(uint32_t, bool, bool, bool, uint8_t, void *, uint8_t));

TEST_F(ProtocolFrameTest, create_valid_can_cc)
{
    char *data = (char *)calloc(8, sizeof(uint8_t));

    strcpy(data, "Test");

    uint32_t id = 0x1;
    bool rtr = false;
    bool ide = false;
    bool edl = false;
    uint8_t dlc = 8;
    uint8_t data_size = 8;

    // expect create to be called once
    EXPECT_GLOBAL_CALL(create_mock, create_mock(id, rtr, ide, edl, dlc, data, data_size)).Times(1);

    // when create is called, delegate (exec) the real method
    ON_GLOBAL_CALL(create_mock, create_mock(id, rtr, ide, edl, dlc, data, data_size))
        .WillByDefault(can::protocol::frame::create);

    frame_res res = create_mock(id, rtr, ide, edl, dlc, data, data_size);

    EXPECT_TRUE(res.has_value());

    frame_t frame = res.value();

    // Assertations

    ASSERT_EQ(id, frame.id.base);
    ASSERT_EQ(0, frame.id.extended);

    ASSERT_EQ(rtr, frame.rtr);
    ASSERT_EQ(ide, frame.ide);
    ASSERT_EQ(edl, frame.edl);
    ASSERT_EQ(frame.rtr, data::RTR::DATA_FRAME);
    ASSERT_EQ(frame.ide, data::IDE::BASE_FORMAT);
    ASSERT_EQ(frame.edl, data::EDL::CC_FRAME);

    ASSERT_EQ(dlc, frame.dlc.dlc);
    ASSERT_EQ(data_size, frame._maxDataSize);

    ASSERT_EQ(frame._type, FrameType::CC);

    ASSERT_EQ(frame._actualdataSize, 8);
    ASSERT_EQ(frame._actualdataSize, dlc);

    ASSERT_EQ(frame.fd_data, nullptr);

    char *res_data_ptr = (char *)&(res.value().data[0]);

    EXPECT_STREQ(data, res_data_ptr);
}