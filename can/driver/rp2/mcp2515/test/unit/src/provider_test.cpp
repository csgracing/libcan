#include "can/driver/rp2/mcp2515/provider.h"

#include <string.h> // memset

#include "provider_test.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gmock-global/gmock-global.h>

#include "mocks/spi.hpp"
#include "mocks/gpio.hpp"

using namespace testing;

std::shared_ptr<MockProvider> ProviderTest::m_provider = NULL;

ProviderTest::ProviderTest() {
};

void ProviderTest::SetUp()
{
    EXPECT_GLOBAL_CALL(spi_init, spi_init(_, _)).Times(1);
    EXPECT_GLOBAL_CALL(spi_set_format, spi_set_format(_, _, _, _, _)).Times(1);
    EXPECT_GLOBAL_CALL(spi_write_blocking, spi_write_blocking(_, _, _)).Times(AtLeast(1));
    EXPECT_GLOBAL_CALL(spi_read_blocking, spi_read_blocking(_, _, _, _)).Times(AtLeast(1));

    m_provider = std::make_shared<MockProvider>();
};

void ProviderTest::TearDown()
{
    m_provider.reset();
};

TEST_F(ProviderTest, registerRawIrqHandlerOnCurrentCore_calls_add_raw_irq_handler)
{
    // Not testing bindToNextIsrId in this fixture, mock to 1.
    EXPECT_CALL(*m_provider, bindToNextIsrId()).Times(1).WillOnce(Return(0));

    // expect to be called once and return real function
    EXPECT_CALL(*m_provider, registerRawIrqHandlerOnCurrentCore()).Times(1).WillOnce([m_provider]()
                                                                                     { return m_provider->CANBus::registerRawIrqHandlerOnCurrentCore(); });

    EXPECT_GLOBAL_CALL(gpio_add_raw_irq_handler, gpio_add_raw_irq_handler(_, _)).Times(1);

    m_provider.get()->registerRawIrqHandlerOnCurrentCore();

    EXPECT_TRUE(Mock::VerifyAndClearExpectations(m_provider.get()));
}

TEST_F(ProviderTest, sendMessage_writes_frame_via_spi)
{
    using namespace can::protocol::classic::frame;

    EXPECT_GLOBAL_CALL(spi_write_blocking, spi_write_blocking(_, _, _)).Times(AtLeast(1));

    // The real chip driver reads back TXBnCTRL to find a free TX buffer before writing
    // (mcp2515.cpp: sendMessage(const can_frame*)). The mock never fills the output
    // buffer, so it must be zeroed explicitly here or ctrlval is uninitialized stack
    // memory and the "is this buffer free" check is non-deterministic.
    EXPECT_GLOBAL_CALL(spi_read_blocking, spi_read_blocking(_, _, _, _))
        .Times(AtLeast(1))
        .WillRepeatedly([](spi_inst_t *, uint8_t, uint8_t *buf, size_t len)
                         { memset(buf, 0, len); return len; });

    uint8_t payload[2] = {0xAB, 0xCD};
    frame_res f = create({
        0x201,           // id
        false,           // rtr
        false,           // ide (extended?)
        false,           // edl (CAN FD?)
        2,               // dlc
        (void *)payload, // data pointer
        dlc_t(8),        // dlc-max for the protocol variant
        2                // actual byte size
    });
    ASSERT_TRUE(f.has_value());

    EXPECT_CALL(*m_provider, sendMessage(_)).Times(1).WillOnce([m_provider](frame_t frame)
                                                                { return m_provider->CANBus::sendMessage(frame); });

    ASSERT_TRUE(m_provider->sendMessage(f.value()));

    EXPECT_TRUE(Mock::VerifyAndClearExpectations(m_provider.get()));
}