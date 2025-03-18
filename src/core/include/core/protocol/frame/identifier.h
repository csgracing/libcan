#ifndef FRAME_IDENTIFIER_H_
#define FRAME_IDENTIFIER_H_

#include <stdint.h> // uint[x]_t

#include <cstddef>    // std::size_t
#include <functional> // std::hash

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

        uint32_t combined() const
        {
            return base | (extended << 11);
        };

        friend bool operator==(const identifier &lhs, const identifier &rhs)
        {
            return lhs.combined() == rhs.combined();
        };

        identifier(uint32_t id)
        {
            base = id & 0b11111111111;
            extended = id >> 11;
        }

        identifier() = default;
    };

    struct identifier_hasher
    {
        std::size_t operator()(const identifier &i) const
        {
            return std::hash<uint32_t>{}(i.combined());
        };
    };
}

#endif /* FRAME_IDENTIFIER_H_ */