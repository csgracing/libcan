#include <iostream>
#include <string.h> // memcpy

#include "core/isotp/tl/parse.h"

namespace can::isotp::tl
{

    // byte 1, bits 7 to 4. (p23 iso15765)
    pci::FrameType GetFrameType(can::frame *frame)
    {
        // first bite, bits 7-4
        return (pci::FrameType)(frame->data[0] >> 4);
    };

    void HandleIncomingFrame(can::frame *frame)
    {
        std::wcout << "Parsing frame with id: ";
        std::wcout << frame->id;
        std::wcout << "\r\n";

        // Check bits 7 to 4 for FrameType
        switch (GetFrameType(frame))
        {
        case pci::FrameType::FIRST_FRAME:
            ProcessFirstFrame(frame);
            break;
        }
    };

    void ProcessFirstFrame(can::frame *frame)
    {
        // determine SF_DL (SingleFrame DataLength)
        if (frame->dlc > 8)
        {
            // CAN FD
        }
        else
        {
            // >=8, CAN 2.0 (Non-FD)
        }
    };
}