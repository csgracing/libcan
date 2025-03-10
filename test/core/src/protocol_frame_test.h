#ifndef SRC_PROTOCOL_FRAME_TEST_H_
#define SRC_PROTOCOL_FRAME_TEST_H_

#include "gtest/gtest.h"

#include "protocol_frame_test_input.h"

// The fixture for testing class Foo.
class ProtocolFrameTest : public ::testing::TestWithParam<create_input>
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
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();

    // static void SetUpTestSuite();
    // static void TearDownTestSuite();

    static std::shared_ptr<can::protocol::frame::frame_res> m_res;
};

#endif /* SRC_PROTOCOL_FRAME_TEST_H_ */