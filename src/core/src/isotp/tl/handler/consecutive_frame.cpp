#include "core/isotp/tl/handler/consecutive_frame.h"

#include "core/isotp/error/code/consecutive_frame.h"
#include "core/isotp/error/code/success.h"

#include <iostream> // std::wcout | debugging

using can::isotp::error::code::ConsecutiveFrameError;
using can::isotp::error::code::Success;

namespace can::isotp::tl::handler
{
    boost::system::error_code ConsecutiveFrameHandler::handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link)
    {
        can::isotp::link::DirectionalLink *recvLink = link->getReceive();

        if (recvLink->getState() != can::isotp::link::LinkState::IN_PROGRESS)
        {
            // not in progress, ignore
            return ConsecutiveFrameError::LINK_STATE_MISMATCH;
        }

        can::isotp::link::directional_link_buf_t *buf = recvLink->getBuffer();

        // parse: sequence number
        can::isotp::tl::pci::cf::SequenceNumber received_sn = can::isotp::tl::pci::cf::SequenceNumber(frame->data[0] & 0x0F); // byte 1 (bits 3-0 inclusive)
        can::isotp::tl::pci::cf::SequenceNumber *last_sn = buf->sequence_number;
        // check if SN is expected
        if (!last_sn->precedes(received_sn))
        {
            // wrong sn
            return ConsecutiveFrameError::PKT_SEQUENCE_NUMBER_MISMATCH;
        }

        // bytes 1+ are data
        // TODO make this kinda thing common in parser for this...
        uint8_t message_start_offset = 1;
        uint8_t payload_size = frame->_bsize.to_ulong() - message_start_offset;
        uint8_t link_remaining_bytes = buf->size - buf->offset;

        // TODO: handle too short?
        if (payload_size > link_remaining_bytes)
        {
            // too long payload, larger than remaining bytes
            return ConsecutiveFrameError::PKT_PAYLOAD_TOO_LONG;
        }

        // copy
        recvLink->copyIntoBuffer(frame->data + message_start_offset, payload_size);

        // copyIntoBuffer will increment offset

        // increment sequenceNumber
        buf->sequence_number->increment();

        // done.

        // check if we have finished receiving
        if (buf->offset >= buf->size)
        {
            // done
            recvLink->setState(can::isotp::link::LinkState::FULL);

            std::wcout << "RX DONE, data:" << std::endl;

            for (int i = 0; i < buf->size; i++)
            {
                std::wcout << std::hex << buf->buffer[i];
            }
            std::wcout << "\r\n";

            // todo: do something here...
        }
        else
        {
            // we still have data to recieve
            // TODO: block size handling
            std::wcout << "STILL RECEIVING" << std::endl;
        }

        return Success::SUCCESS;
    };
}