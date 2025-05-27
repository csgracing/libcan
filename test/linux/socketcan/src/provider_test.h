#ifndef SRC_PROVIDER_TEST_H_
#define SRC_PROVIDER_TEST_H_

#include "gtest/gtest.h"

#include <linux/socketcan/provider.h>

// The fixture for testing class Foo.
class LinuxSocketcanProviderTest : public ::testing::Test
{

protected:
    // You can do set-up work for each test here.
    LinuxSocketcanProviderTest() = default;

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~LinuxSocketcanProviderTest() = default; // default impl

    static void SetUpTestSuite();
    static void TearDownTestSuite();

    void SetUp();
    // void TearDown();

    static std::shared_ptr<can::providers::os::socketcan::CANBus> m_cb;
    static std::shared_ptr<sockcanpp::CanDriver> m_testDriver;
};

#endif /* SRC_PROVIDER_TEST_H_ */