#include <gmock/gmock.h> // Brings in gMock.

// impl
#include "rp2040/mcp2515/provider.h"

using namespace can::providers::rp2040::mcp2515;

class MockProvider : public CANBus
{
public:
    can::providers::rp2040::mcp2515::Options o;

    MockProvider() : CANBus(
                         (can::providers::base::bitrate_enum_t)Bitrate::BITRATE_1000000,
                         (can::providers::base::options_t)o) {};

    MOCK_METHOD(uint8_t, bindToNextIsrId, ());
    MOCK_METHOD(void, rawIrqHandler, ());

    MOCK_METHOD(can::frame_read_res, readMessage, ());

    MOCK_METHOD(void, global_isr_0, ());
    MOCK_METHOD(void, global_isr_1, ());

    // MOCK_METHOD(void, registerRawIrqHandlerOnCurrentCore, ());
};