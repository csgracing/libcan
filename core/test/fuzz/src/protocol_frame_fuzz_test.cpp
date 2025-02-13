#include <fuzztest/fuzztest.h>

#include "core/protocol/frame/frame.h"

#include "protocol_frame_fuzz_test.h"

using namespace can::protocol::frame;

void TestFuzzThing(std::array<char, 8> data)
{

    char *data_ptr = (char *)data.data();

    frame_res res = create({0x1,
                            false,
                            false,
                            false,
                            8,
                            data_ptr,
                            dlc_t(8),
                            8});

    ASSERT_TRUE(res.has_value());
}

FUZZ_TEST(ProtocolFrameFuzzTest, TestFuzzThing)
    //.WithDomains(/*i:*/ fuzztest::Positive<int>()
    .WithDomains(fuzztest::ArrayOf<8>(fuzztest::Arbitrary<char>()));
