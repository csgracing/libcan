#include "core/isotp/tl/handler/single_frame.h"

#include "core/isotp/tl/pci/single_frame.h"

#include <iostream> // std::wcout | debugging

namespace can::isotp::tl::handler
{
    void SingleFrameHandler::handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link)
    {

        uint8_t sf_dl;

        // determine SF_DL (SingleFrame DataLength)
        // check against frametype bitmask
        if (can::protocol::frame::isType(frame->_type, can::protocol::frame::FrameType::CC))
        {
            std::wcout << "CAN_CC\r\nSF_DL: ";
            // CAN CC

            // SF_DL 4 byte value lower 4 bits (3-0) in byte #1
            sf_dl = frame->data[0] & 0b1111;
            std::wcout << sf_dl;
            std::wcout << "\r\n";

            uint8_t length;

            // sf_dl handling
            // 9.6.2.2
            if (sf_dl == pci::sf::cc::DATA_LENGTH_RESERVED)
            {
                // ignore the SF TL_PDU (this frame?)
                return;
            }
            else if (sf_dl >= pci::sf::cc::DATA_LENGTH_1 && sf_dl <= pci::sf::cc::DATA_LEGNTH_6)
            {
                // "SF_DL is assigned value of service param 'length'"
                length = sf_dl;
            }
            else if (sf_dl == pci::sf::cc::DATA_LENGTH_7)
            {
                // same as previous but only allowed with normal addressing
                if (frame->ide == can::protocol::frame::data::IDE::EXTENDED_FORMAT)
                {
                    // invalid as is using extended format, ignore
                    return;
                }
                else
                {
                    // set as service param length
                    length = sf_dl;
                }
            }
            else
            {
                // other values are invalid
                return;
            }

            // length is set (otherwise would have returned)
            // CC frame so read starting from byte 2 length bits

            // sanity check: is length+1 > 8
            if (length + 1 > 8)
            {
                return;
            }

            // read
            uint8_t *message_ptr = new uint8_t[length];
            uint8_t *data = frame->data;
            // offset by 1 for message data (CC frame)
            memcpy(message_ptr, data + 1, length);

            std::wcout << "SINGLE FRAME:";
            for (int i = 0; i < length; i++)
            {
                std::wcout << std::hex << message_ptr[i];
            }
            std::wcout << "\r\n";
        }
        else if (can::protocol::frame::isType(frame->_type, can::protocol::frame::FrameType::FD))
        {
            // CAN FD

            // Check if SD_DL lower 4 bits (byte #1, bits 3-0) are 0
            if (frame->data[0] << 4 != 0)
            {
                // ignore frame
                return;
            }
            else
            {
                // valid

                // SF_DL 8 bit value from byte #2
                // Message data start offset+1
                sf_dl = frame->data[1];

                // TODO: handle
            }
        }
        else
        {
            // Unknown
            // TODO: count rx / parse errors.
            return;
        }
    };
}