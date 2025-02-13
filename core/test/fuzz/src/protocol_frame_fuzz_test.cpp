
#include <fuzztest/fuzztest.h>

#include "gtest/gtest.h"

#include "core/protocol/frame/frame.h"

using namespace can::protocol::frame;

void cc_all_valid_data_sizes(std::vector<char> data)
{

    // cheat-ish way to get char* from std::vector
    char *data_ptr = &data[0];

    uint8_t size = data.size();

    frame_res res = create({0x1,      // id
                            false,    // rtr
                            false,    // ide
                            false,    // edl
                            size,     // dlc
                            data_ptr, // data (ptr)
                            dlc_t(8), // dlc max for proto
                            size});   // byte size

    ASSERT_TRUE(res.has_value());
}
void cc_all_valid_data_sizes_with_dlc_above_8(std::vector<char> data)
{

    // cheat-ish way to get char* from std::vector
    char *data_ptr = &data[0];

    uint8_t size = data.size();
    // cap byte_size at 8
    // don't read past but have dlc values up to 15 inclusive
    uint8_t byte_size = std::min(size, (uint8_t)8);

    frame_res res = create({0x1,         // id
                            false,       // rtr
                            false,       // ide
                            false,       // edl
                            size,        // dlc
                            data_ptr,    // data (ptr)
                            dlc_t(8),    // dlc max for proto
                            byte_size}); // byte size

    ASSERT_TRUE(res.has_value());
}

FUZZ_TEST(ProtocolFrameFuzzTest, cc_all_valid_data_sizes)
    .WithDomains(fuzztest::VectorOf(fuzztest::Arbitrary<char>()).WithMinSize(0).WithMaxSize(8));

FUZZ_TEST(ProtocolFrameFuzzTest, cc_all_valid_data_sizes_with_dlc_above_8)
    .WithDomains(fuzztest::VectorOf(fuzztest::Arbitrary<char>()).WithMinSize(0).WithMaxSize(15));
