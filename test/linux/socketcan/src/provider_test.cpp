#include "provider_test.h"

using namespace can::providers::os::socketcan;
using namespace can::protocol::frame;

std::shared_ptr<CANBus> LinuxSocketcanProviderTest::m_cb = NULL;
std::shared_ptr<sockcanpp::CanDriver> LinuxSocketcanProviderTest::m_testDriver = NULL;

void LinuxSocketcanProviderTest::SetUpTestSuite()
{
    Options *o = new Options();
    o->canInterface = "vcan0";
    o->canProtocol = CAN_RAW;
    m_cb = std::make_shared<CANBus>(NULL, o);

    // setup canDriver for sending
    m_testDriver = std::make_shared<sockcanpp::CanDriver>("vcan0", CAN_RAW, 0, 0);
};

void LinuxSocketcanProviderTest::TearDownTestSuite()
{
    m_cb.reset();
    m_testDriver.reset();
};

void LinuxSocketcanProviderTest::SetUp()
{
    // remove any messages in the queue before each test runs
    bool hasMessage = true;
    while (hasMessage)
    {
        hasMessage = m_cb->hasMessage();
    }

    ASSERT_FALSE(m_cb->hasMessage());
};

TEST_F(LinuxSocketcanProviderTest, testSendMessage)
{
    // send message using other lib
    can_frame d_frame;
    char *data = (char *)calloc(8, sizeof(char));
    memcpy(d_frame.data, data, 8);
    d_frame.can_id = 0x123;
    d_frame.can_dlc = 8;

    m_testDriver->sendMessage(d_frame);

    ASSERT_TRUE(m_cb->hasMessage());

    frame_res res = m_cb->readMessage();
    ASSERT_TRUE(res.has_value());

    frame_t frame = res.value();
};
