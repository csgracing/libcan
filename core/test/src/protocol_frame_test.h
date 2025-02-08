#include "gtest/gtest.h"

#include "core/protocol/frame/frame.h"

// The fixture for testing class Foo.
class ProtocolFrameTest : public ::testing::Test
{

protected:
    // You can do set-up work for each test here.
    ProtocolFrameTest() = default;

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~ProtocolFrameTest() = default; // default impl

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    // virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    // virtual void TearDown();

    // static void SetUpTestSuite();
    // static void TearDownTestSuite();

    can::protocol::frame::frame_res callAndExpectCreate(uint32_t id, bool rtr, bool ide, bool edl, uint8_t dlc, void *__restrict__ data, uint8_t data_size);
};