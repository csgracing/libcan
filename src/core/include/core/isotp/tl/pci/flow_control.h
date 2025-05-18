#ifndef PCI_FLOW_CONTROL_H_
#define PCI_FLOW_CONTROL_H_

#include <cstdint> // uint8_t

namespace can::isotp::tl::pci
{
    /**
     * FlowControl TL_PCI parameter definition
     *
     * @cite ISO 17565-2:2024, 9.6.5 "FlowControl TL_PCI parameter definition"
     */
    namespace fc
    {
        // "enum class" so members must be accessed via FlowStatus::

        /**
         * FlowStatus (FS) parameter definition.
         *
         * Indicates if the sender can proceed with the message transmission.
         * We should support all non-reserved values of the parameter.fc
         *
         * This parameter is also known as C(sub)(TL_FCFS)
         *
         * @cite ISO 15765-2:2024, 9.6.5.1 "FlowStatus (FS) parameter definition"
         */
        class FlowStatus
        {

        public:
            enum Value
            {
                /**
                 * Causes the sender to resume sending ConsecutiveFrames.
                 *
                 * When received in a FC frame, this indicates that the receiver is ready to recieve <=BlockSize number of ConsecutiveFrames.
                 */
                CONTINUE_TO_SEND = 0x0,

                /**
                 * Causes the sender to wait for a new FlowControl PDU (frame) and restart it's BlockSize counter.
                 *
                 * Note: if FlowStatus is set to this value, the BlockSize and STmin contained in the FC message should be ignored.
                 */
                WAIT = 0x1,

                /**
                 * Causes the sender to abort the segmented message transmission.fc
                 * (see spec)
                 */
                OVERFLOW = 0x2,

                RESERVED_3 = 0x3,
                RESERVED_4 = 0x4,
                RESERVED_5 = 0x5,
                RESERVED_6 = 0x6,
                RESERVED_7 = 0x7,
                RESERVED_8 = 0x8,
                RESERVED_9 = 0x9,
                RESERVED_A = 0xA,
                RESERVED_B = 0xB,
                RESERVED_C = 0xC,
                RESERVED_D = 0xD,
                RESERVED_E = 0xE,
                RESERVED_F = 0xF,
            };

            // JC: allow creating from uint8_t value
            // TODO: unsafe if invalid value passed?

            FlowStatus(uint8_t absValue) : type((Value)(absValue)) {};

            // below impl based on: https://stackoverflow.com/a/53284026

            FlowStatus() = default;
            constexpr FlowStatus(Value aType) : type(aType) {};

            // Allow switch and comparisons.
            constexpr operator Value() const { return type; }

            // Prevent usage: if(fruit)
            explicit operator bool() const = delete;

        private:
            Value type;
        };
    }
}

#endif /* PCI_FLOW_CONTROL_H_ */