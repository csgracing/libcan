#ifndef FUZZ_PROTOCOL_FRAME_TEST_H_
#define FUZZ_PROTOCOL_FRAME_TEST_H_

#include "gtest/gtest.h"

// The fixture for testing class Foo.
class ProtocolFrameFuzzTest : public ::testing::Test
{

protected:
    // You can do set-up work for each test here.
    ProtocolFrameFuzzTest() = default;

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~ProtocolFrameFuzzTest() = default; // default impl

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

    // static std::shared_ptr<can::protocol::frame::frame_res> m_res;
};

#endif /* FUZZ_PROTOCOL_FRAME_TEST_H_ */