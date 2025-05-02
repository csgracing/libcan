#ifndef PCI_FRAME_TYPE_H_
#define PCI_FRAME_TYPE_H_

#include <cstdint> // uint8_t

#include "core/protocol/frame/frame.h"

namespace can::isotp::tl
{
    /**
     * Protocol Control Information
     * @cite ISO 15765-2:2024, 9.6 "Protocol control information specification"
     */
    namespace pci
    {
        /**
         * @cite ISO 15765-2:2024, 9.6.1 TL_PCI, Table 9
         */
        class FrameType
        {
        public:
            enum Value : uint8_t
            {
                SINGLE_FRAME = 0b0000,       // 0x0
                FIRST_FRAME = 0b0001,        // 0x1
                CONSECUTIVE_FRAME = 0b0010,  // 0x2
                FLOW_CONTROL_FRAME = 0b0011, // 0x3
                // 0b0100 (0x4)-> 0b1111 (0xF) are reserved
            };

            // JC: allow creating from uint8_t value
            // TODO: unsafe if invalid value passed?

            FrameType(uint8_t absValue) : type((Value)(absValue)) {};

            // below impl based on: https://stackoverflow.com/a/53284026

            FrameType() = default;
            constexpr FrameType(Value aType) : type(aType) {};

            // Allow switch and comparisons.
            constexpr operator Value() const { return type; }

            // Prevent usage: if(fruit)
            explicit operator bool() const = delete;

            struct frame_type_hasher
            {
                std::size_t operator()(const FrameType &i) const
                {
                    return std::hash<uint32_t>{}(i.type);
                };
            };

            static const inline pci::FrameType GetFrameType(can::protocol::frame::frame_t *frame)
            {
                // first bite, bits 7-4
                return pci::FrameType(frame->data[0] >> 4);
            };

        private:
            Value type;
        };
    }
}

#endif /* PCI_FRAME_TYPE_H_ */