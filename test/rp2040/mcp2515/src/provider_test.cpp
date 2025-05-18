#include "rp2040/mcp2515/provider.h"

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