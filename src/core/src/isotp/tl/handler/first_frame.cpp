#include "core/isotp/tl/handler/first_frame.h"

#include "core/isotp/error/code/first_frame.h"
#include "core/isotp/error/code/success.h"

#include "core/isotp/tl/pdu/flow_control.h"

#include "core/logger.h"

using can::isotp::error::code::FirstFrameError;
using can::isotp::error::code::Success;

namespace can::isotp::tl::handler
{
    boost::system::error_code FirstFrameHandler::handle(can::protocol::frame::frame_t *frame, can::isotp::link::ISOTPLink *link)
    {

        LIBCAN_LOG_TRACE("isotp.tl.handler", "Handling FirstFrame");
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

        LIBCAN_LOG_TRACE("isotp.tl.handler", "FirstFrame has FF_DL of {0:#x} ({0:d})", ff_dl, ff_dl);

        // 3. Validate FF_DL

        if (ff_dl < 8)
        {
            // ignore (no reason to use TP signalling) (9.6.3.2 paragraph 1)
            // TODO: stub
            return FirstFrameError::PKT_UNEXPECTED_SIGNALLING;
        }

        // TODO: check if greater than max buf size when passed to this func

        // valid
        // TODO: refactor into more than one method!

        // -- validation has passed.

        // -- Directional Entry Creation

        // allocate link buffer of size ff_dl
        can::isotp::link::DirectionalLink *recvLink = link->getReceive();
        recvLink->setState(can::isotp::link::LinkState::IN_PROGRESS);
        recvLink->allocateBuffer(ff_dl);

        // determine how much to copy this frame & start byte
        LIBCAN_LOG_TRACE("isotp.tl.handler", "FirstFrame has message offset of {0:d}", message_start_offset);

        uint32_t length = frame->_bsize.to_ulong() - message_start_offset;

        LIBCAN_LOG_TRACE("isotp.tl.handler", "copying FirstFrame data of size {0:d}", length);

        // copy into buffer
        recvLink->copyIntoBuffer(frame->data + message_start_offset, length);

        // -- Response sending (TODO)

        // for now we just print.
        can::isotp::link::directional_link_buf_t *buf = recvLink->getBuffer();

        // print current and  max len/size
        LIBCAN_LOG_TRACE("isotp.tl.handler", "RX directional buffer has {0:d} of {0:d} bytes received", buf->offset, buf->size);

        LIBCAN_LOG_TRACE_BUF("isotp.tl.handler", buf->buffer, buf->offset, "RX directional buffer contains data: {}");

        // next up, send next pkt..

        // FC TL_PDU(CTS)

        can::isotp::tl::pci::fc::FlowStatus status = can::isotp::tl::pci::fc::FlowStatus::CONTINUE_TO_SEND;
        can::isotp::tl::pdu::FlowControl *fc = new can::isotp::tl::pdu::FlowControl(status, 0x0, 0x0);

        uint8_t *payload = fc->createPayload();
        uint8_t payload_size = fc->getPayloadSize();
        can::protocol::frame::frame_res res = link->getBus()->createFrame(link->getSend()->getId(), payload, payload_size);

        if (res.has_value())
        {
            can::protocol::frame::frame_t frame = res.value();

            LIBCAN_LOG_TRACE_BUF("isotp.tl.handler", frame.data, frame._bsize.to_ulong(), "Response FlowControl frame contains data: {}");

            link->getBus()->enqueue(frame);
        }
        else
        {
            // todo handle error parsing here...
            LIBCAN_LOG_ERROR("isotp.tl.handler", "FC frame was not created properly (no return value from createFrame)");
        }

        return Success::SUCCESS;
    };
}