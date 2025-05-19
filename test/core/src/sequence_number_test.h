#ifndef SRC_SEQUENCE_NUMBER_TEST_H_
#define SRC_SEQUENCE_NUMBER_TEST_H_

#include "gtest/gtest.h"

// The fixture for testing class Foo.
class SequenceNumberTest : public ::testing::Test
{

protected:
    // You can do set-up work for each test here.
    SequenceNumberTest() = default;

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~SequenceNumberTest() = default; // default impl
};

#endif /* SRC_SEQUENCE_NUMBER_TEST_H_ */