#ifndef PCI_CONSECUTIVE_FRAME_H_
#define PCI_CONSECUTIVE_FRAME_H_

#include <bitset>

#include <cstdint> // uint8_t

namespace can::isotp::tl::pci
{
    /**
     * ConsecutiveFrame TL_PCI parameter definition
     *
     * @cite ISO 17565-2:2024, 9.6.4 "ConsecutiveFrame TL_PCI parameter definition"
     */
    namespace cf
    {
        class SequenceNumber
        {
        private:
            // Static so only one instace of var (prevents things like usage of the variable when not initialised yet resulting in random values)
            static const uint8_t INITIAL_VALUE = 0b0000;
            static const uint8_t MAX_VALUE = 0b1111;

            std::bitset<4> *num;

        public:
            SequenceNumber() : SequenceNumber(INITIAL_VALUE) {};
            SequenceNumber(uint8_t val) { num = new std::bitset<4>(val); };

            // returns true if overflowed
            // TODO: unit testing
            inline bool increment()
            {
                if (num->operator==(MAX_VALUE))
                {
                    // overflow: true
                    num->reset();
                    return true;
                }
                else
                {
                    // overflow: false
                    num = new std::bitset<4>(value() + 1);
                    return false;
                }
            }

            inline uint8_t value()
            {
                return num->to_ulong();
            }

            // returns true if self value+1 would be other value
            inline bool precedes(SequenceNumber other)
            {
                if (num->operator==(MAX_VALUE))
                {
                    return other.value() == INITIAL_VALUE;
                }
                else
                {
                    return (value() + 1) == other.value();
                }
            }
        };
    }
}

#endif /* PCI_CONSECUTIVE_FRAME_H_ */