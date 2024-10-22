#ifndef SRC_MESSAGE_H_
#define SRC_MESSAGE_H_

#include <stdint.h>

namespace can
{

    // https://github.com/KevinOConnor/can2040/blob/9e761ae353ea473e24c8bba226e10afad8a919ff/src/can2040.h#L6
    typedef struct
    {

        uint32_t id;
        // Data length code (normally 0-8 inclusive) [uint32_t]
        uint32_t dlc;
        union
        {
            uint8_t data[8];
            uint32_t data32[2];
        };
    } frame;
};

#endif /* SRC_MESSAGE_H_ */