#include "gtest/gtest.h"

#include "tap.h"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);

    testing::TestEventListeners &listeners = testing::UnitTest::GetInstance()->listeners();
    // delete listeners.Release(listeners.default_result_printer());
    listeners.Append(new tap::TapListener());

    int result = RUN_ALL_TESTS();
    return result;
}