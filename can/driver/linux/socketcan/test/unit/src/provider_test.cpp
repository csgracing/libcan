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

TEST_F(LinuxSocketcanProviderTest, testReadMessage)
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

TEST_F(LinuxSocketcanProviderTest, testReadMessageNoneQueued)
{
    ASSERT_FALSE(m_cb->hasMessage());
    ASSERT_EQ(m_cb->readMessage(), std::nullopt);
};

TEST_F(LinuxSocketcanProviderTest, testSendMessage)
{
    std::string data("12345678");

    frame_res msg = can::protocol::frame::create({0x321,                // id
                                                  false,                // rtr
                                                  false,                // ide
                                                  false,                // edl
                                                  8,                    // dlc
                                                  (void *)data.c_str(), // data (ptr)
                                                  dlc_t(8),             // dlc max for proto
                                                  8});                  // byte size
    ASSERT_TRUE(msg.has_value());

    // prepare to send
    ASSERT_FALSE(m_cb->hasMessage());

    // send and rx same mesasge
    m_cb->enqueue(msg.value()); // place message in TX queue

    m_cb->handleQueue(); // transmit

    ASSERT_TRUE(m_testDriver->waitForMessages(std::chrono::milliseconds(0)));

    sockcanpp::CanMessage recv = m_testDriver->readMessage();
    uint32_t recvId = recv.getCanId();
    std::string recvData = recv.getFrameData();

    ASSERT_EQ(msg.value().id.combined(), recvId);
    ASSERT_EQ(data, recvData);
};