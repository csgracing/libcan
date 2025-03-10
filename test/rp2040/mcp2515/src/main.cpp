#include "gtest/gtest.h"

#include "mocks/provider.h"

Options *o = new Options();

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    int result = RUN_ALL_TESTS();
    return result;
}