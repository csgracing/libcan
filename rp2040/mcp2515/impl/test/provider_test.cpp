#include "rp2040/mcp2515/provider.h"

#include "provider_test.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <gmock-global/gmock-global.h>

#include "mocks/spi.hpp"
#include "mocks/gpio.hpp"

using namespace testing;

// ProviderTest::ProviderTest()
//{
//     ON_CALL(m_provider.chip, reset()).WillByDefault(Return(MCP2515::ERROR_OK));
//     ON_CALL(m_provider.chip, setBitrate()).WillByDefault(Return(MCP2515::ERROR_OK));
//     ON_CALL(m_provider.chip, setNormalMode()).WillByDefault(Return(MCP2515::ERROR_OK));
// }

ProviderTest::ProviderTest() {
    // ON_GLOBAL_NICE_CALL(spi_init, spi_init(_, _)).WillByDefault(testing::Return(0));
    // ON_GLOBAL_NICE_CALL(spi_init, spi_init(_, _)).WillByDefault(Return(0));
    // EXPECT_GLOBAL_CALL(spi_init, spi_init(_, _));
    // ASSERT_EQ(1, 1);
};

void ProviderTest::SetUp() {};

void ProviderTest::TearDown() {};

void ProviderTest::SetUpTestSuite()
{
    EXPECT_GLOBAL_CALL(spi_init, spi_init(_, _)).Times(1);
    EXPECT_GLOBAL_CALL(spi_set_format, spi_set_format(_, _, _, _, _)).Times(1);
    EXPECT_GLOBAL_CALL(spi_write_blocking, spi_write_blocking(_, _, _)).Times(AtLeast(1));
    EXPECT_GLOBAL_CALL(spi_read_blocking, spi_read_blocking(_, _, _, _)).Times(AtLeast(1));
    MockProvider mp = MockProvider();
    m_provider = &mp;
};

void ProviderTest::TearDownTestSuite()
{
    MockProvider &mp = *m_provider;
    m_provider = nullptr;
};

TEST_F(ProviderTest, registerRawIrqHandlerOnCurrentCore)
{
    // get a reference of m_provider
    MockProvider &m = *m_provider;

    EXPECT_CALL(m, bindToNextIsrId()).Times(1).WillOnce(Return(0));
    // EXPECT_CALL(*m_provider, registerRawIrqHandlerOnCurrentCore()).Times(1);

    EXPECT_GLOBAL_CALL(gpio_add_raw_irq_handler, gpio_add_raw_irq_handler(_, _)).Times(1);

    m_provider->registerRawIrqHandlerOnCurrentCore();
    ;
}
