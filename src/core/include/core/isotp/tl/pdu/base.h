#ifndef PDU_BASE_H_
#define PDU_BASE_H_

#include "core/isotp/link/link.h"
#include "core/isotp/tl/pci/frame_type.h"
#include "core/protocol/frame/frame.h"

namespace can::isotp::tl
{
    /**
     * Protocol Data Unit
     * @cite ISO 15765-2:2024, 9.4 "Protocol data unit types"
     */
    namespace pdu
    {

        class Base
        {
        private:
            can::isotp::tl::pci::FrameType type;
            uint8_t payload_size;

        public:
            Base(can::isotp::tl::pci::FrameType type, uint8_t payload_size);
            // virtual ~Base(); // desructor

            inline can::isotp::tl::pci::FrameType getType() { return type; };
            inline uint8_t getPayloadSize() { return payload_size; };

            // derived classes must provide an implementation (=0)
            // <https://stackoverflow.com/a/2089238>

            virtual uint8_t *createPayload() = 0;
        };
    }
}

#endif /* PDU_BASE_H_ */