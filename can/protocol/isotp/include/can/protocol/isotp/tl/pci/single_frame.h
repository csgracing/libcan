#ifndef DL_SINGLE_FRAME_H_
#define DL_SINGLE_FRAME_H_

namespace can::isotp::tl::pci
{
    /**
     * SingleFrame TL_PCI parameter definition
     *
     * @cite ISO 17565-2:2024, 9.6.2 "SingleFrame TL_PCI parameter definition"
     */
    namespace sf
    {

        namespace cc
        {
            /**
             * Single Frame data length (SF_DL)
             * (CAN_DL is less than or equal to 8)
             * @cite ISO 15765-2:2024, 9.6.2.1 "SF TL_PCI byte", Table 11
             */
            enum DataLength
            {
                /* 0b0000 reserved */
                DATA_LENGTH_RESERVED = 0b0000,

                DATA_LENGTH_1 = 0b0001,
                DATA_LENGTH_2 = 0b0010,
                DATA_LENGTH_3 = 0b0011,
                DATA_LENGTH_4 = 0b0100,
                DATA_LENGTH_5 = 0b0101,
                DATA_LEGNTH_6 = 0b0110,

                /**
                 * [SF_DL] with normal addressing only
                 * DATA_LENGTH_7 (SF_DL=7) is only allowed with normal addressing
                 */
                DATA_LENGTH_7 = 0b0111
            };
        }
    }
}

#endif /* DL_SINGLE_FRAME_H_ */