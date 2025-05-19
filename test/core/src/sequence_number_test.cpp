#include "sequence_number_test.h"

#include "core/isotp/link/directional_link.h"

using can::isotp::tl::pci::cf::SequenceNumber;

TEST_F(SequenceNumberTest, initialisationNewDefValue)
{
    SequenceNumber *sn = new SequenceNumber();
    ASSERT_EQ(sn->value(), 0);
};

TEST_F(SequenceNumberTest, initialisationIncrementPrecedes)
{
    for (int i = 0; i <= 0xF0; i++)
    {
        SequenceNumber sn(i);
        // 0xF max value, 0x10 will be 0x0
        ASSERT_EQ(sn.value(), i % 0x10);

        int j = i;
        while (j < 0xF0)
        {
            SequenceNumber *sn2 = new SequenceNumber(sn.value());
            bool overflow = sn.increment();
            j++;
            ASSERT_EQ(overflow, j % 0x10 == 0); // assert that returns true when overflowing
            ASSERT_EQ(sn.value(), j % 0x10);    // assert that value never exceeds 0xF (0b1111)
            ASSERT_TRUE(sn2->precedes(sn));     // assert that incremente'd is always preceded by prev (including when overflowing)
            delete sn2;
        }
    };
};