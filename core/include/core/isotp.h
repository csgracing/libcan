#ifndef SRC_ISOTP_H_
#define SRC_ISOTP_H_

#include <stdint.h>

namespace can::isotp
{
    /**
     * Transport Layer [Protocol]
     * @cite ISO 15765-2:2024, 9 "Transport layer protocol"
     */
    namespace tl
    {

        /**
         * Protocol Control Information
         * @cite ISO 15765-2:2024, 9.6 "Protocol control information specification"
         */
        namespace pci
        {
            typedef struct Frame
            {
                uint8_t type : 4;
            };

            typedef struct SingleFrame
            {
                Frame frame;
            };
        };
    };
}

#endif /* SRC_ISOTP_H_ */