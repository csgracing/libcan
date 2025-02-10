#ifndef FRAME_IDENTIFIER_H_
#define FRAME_IDENTIFIER_H_

#include <stdint.h> // uint[x]_t

namespace can::protocol::frame
{
    /**
     * CAN frame identifier field.
     *
     */
    struct identifier
    {
        /** base identifier (11 bits), CAN 2.0A */
        uint16_t base : 11;
        /** extended identifier (18 bits).
         * combine with base to create CAN 2.0B extended identifier (29 bits)
         */
        uint32_t extended : 18;

        inline uint32_t combined()
        {
            return base | (extended << 11);
        }
    };
}

#endif /* FRAME_IDENTIFIER_H_ */