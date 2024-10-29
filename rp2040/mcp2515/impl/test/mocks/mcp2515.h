#include <gmock/gmock.h> // Brings in gMock.

// pico-mcp2515
#include "mcp2515/mcp2515.h"

using namespace can::providers::rp2040::mcp2515;

class MockMCP2515 : MCP2515
{
    MOCK_METHOD(MCP2515::ERROR, setBitrate, ());
    MOCK_METHOD(MCP2515::ERROR, setNormalMode, ());
};