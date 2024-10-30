#include "gtest/gtest.h"
#include "mocks/provider.h"

// The fixture for testing class Foo.
class ProviderTest : public ::testing::Test
{

protected:
    // You can do set-up work for each test here.
    ProviderTest();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~ProviderTest() = default; // default impl

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    // static void SetUpTestSuite();
    // static void TearDownTestSuite();

    static std::shared_ptr<MockProvider> m_provider;
};