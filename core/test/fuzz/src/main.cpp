#include "gtest/gtest.h"

#include "protocol_frame_fuzz_test.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}