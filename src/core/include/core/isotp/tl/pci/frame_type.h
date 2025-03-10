#ifndef PCI_FRAME_TYPE_H_
#define PCI_FRAME_TYPE_H_

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
        enum FrameType
        {
            SINGLE_FRAME = 0b0000,       // 0x0
            FIRST_FRAME = 0b0001,        // 0x1
            CONSECUTIVE_FRAME = 0b0010,  // 0x2
            FLOW_CONTROL_FRAME = 0b0011, // 0x3
            // 0b0100 (0x4)-> 0b1111 (0xF) are reserved
        };
    }
}

#endif /* PCI_FRAME_TYPE_H_ */