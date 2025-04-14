#include <iostream>
#include <string.h> // memcpy

#include "core/isotp/tl/parse.h"

#include "core/isotp/tl/pci/single_frame.h"

#include "core/protocol/frame/frame.h"

using namespace can::isotp::tl::pci;

namespace can::isotp::tl
{

    // byte 1, bits 7 to 4. (p23 iso15765)
    pci::FrameType GetFrameType(can::protocol::frame::frame_t *frame)
    {
        // first bite, bits 7-4
        return (pci::FrameType)(frame->data[0] >> 4);
    };

    void HandleIncomingFrame(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link)
    {
        std::wcout << "Parsing frame with id: " << std::hex << frame->id.combined() << "\n";
        std::wcout << "Parsing frame with type: " << GetFrameType(frame) << "\n";

        // Check bits 7 to 4 for FrameType
        switch (GetFrameType(frame))
        {
        case pci::FrameType::SINGLE_FRAME:
            ProcessSingleFrame(frame, link);
            break;
        case pci::FrameType::FIRST_FRAME:
            ProcessFirstFrame(frame, link);
            break;
        }
    };

    void ProcessSingleFrame(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link)
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

    void ProcessFirstFrame(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link)
    {
        std::wcout << "FF_PARSE\n";
        /**
         * 1) Check RX_DL (done in frame parsing?)
         * 2) check FF_DL 12-bit (see if large msg)
         */

        // RX_DL is frame->_bsize (after accounting for 8+ byte FD messages)

        // 1. Calculate min data length

        // MINIMUM data length for first frame
        uint32_t min_ff_dl;

        bool isExtendedAddressing = can::protocol::frame::isType(frame->_type, can::protocol::frame::FrameType::UNKNOWN_EXTENDED);

        // TODO: frame->_max_dlc never set/used.
        if (frame->_max_dlc == can::protocol::frame::MaxDLC::MAX_DLC_CC)
        {
            // If extended addressing, FF_DL (min) is 7, otherwise 8 (normal addressing)
            min_ff_dl = isExtendedAddressing ? 7 : 8;
        }
        else if (frame->_max_dlc == can::protocol::frame::MaxDLC::MAX_DLC_FD)
        {
            // If extended addressing, FF_DL (min) is bsize-2, otherwise bsize-1 (normal addressing)
            min_ff_dl = isExtendedAddressing ? (frame->_bsize.to_ulong() - 2) : (frame->_bsize.to_ulong() - 1);
        }
        else
        {
            // TODO: should never be called, return error status just in case
        }

        // 2. Calc FF_DL

        // 2.1 Get 12 bit value from byte 1 and byte 2
        uint8_t ff_dl_high = frame->data[0] << 4; // byte 1 (bits 3-0 inclusive)
        uint8_t ff_dl_low = frame->data[1];       // byte 2

        // bytes 3+ (starting from 1 as per spec) are data IF FF_DL != 0
        // why uint32_t?
        uint32_t message_start_offset = 2;

        // first pass (assume CC)
        // bytes 3+ (starting from 1 as per spec) are data
        uint32_t ff_dl = (ff_dl_high << 8) + (ff_dl_low);

        // std::wcout << "HIGH: " << ff_dl_high << ", LOW: " << ff_dl_low << ", DL: " << ff_dl << "\n";

        // FD check
        if (ff_dl == 0)
        {
            // value from bytes 1+2 are 0 therefore get 32-bit value from byte3 through 6 inclusive, message data starting at offset +4 (2+4)
            message_start_offset += 4; // now 6 (bytes 1-6 are control bytes)

            // bytes #3-6 inclusive, 3 msb (big endian)

            // get bytes #3-6 inclusive (starting from 1)
            uint8_t *data = frame->data;
            memcpy(&ff_dl, data + 2, 4); // from byte 2 (#3) copy 4 bytes to ff_dl_32b

            // make big endian
        }

        // ff_dl now set
        // check for valid FF_DL and process first frame

        std::wcout << "FF: 0x" << std::hex << ff_dl << " (" << std::dec << ff_dl << ")\n";

        // 3. Validate FF_DL

        if (ff_dl < 8)
        {
            // ignore (no reason to use TP signalling) (9.6.3.2 paragraph 1)
            // TODO: stub
            return;
        }

        // TODO: check if greater than max buf size when passed to this func

        // valid
        // TODO: refactor into more than one method!

        // -- validation has passed.

        // -- Directional Entry Creation

        // allocate link buffer of size ff_dl
        can::isotp::link::DirectionalLink *recvLink = link->getReceive();
        recvLink->allocateBuffer(ff_dl);

        // determine how much to copy this frame & start byte
        std::wcout << "MSG_OFFSET: " << std::dec << message_start_offset << "\n";

        uint32_t length = frame->_bsize.to_ulong() - message_start_offset;

        std::wcout << "Copying data of size: " << std::dec << length << "\n";
        // copy into buffer
        recvLink->copyIntoBuffer(frame->data + message_start_offset, length);

        // -- Response sending (TODO)

        // for now we just print.
        can::isotp::link::directional_link_buf_t *buf = recvLink->getBuffer();

        // print current and  max len/size
        std::wcout << "Buffer (" << std::dec << buf->offset << " of " << std::dec << buf->size << " bytes received)\r\n";

        for (int i = 0; i < buf->offset; i++)
        {
            std::wcout << std::hex << buf->buffer[i];
        }
        std::wcout << "\r\n";

        // next up, send next pkt..
    };
}