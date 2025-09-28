
# libcan/tests README

This README provides an overview of the main test files and directories in the `libcan/tests` folder. It summarizes the purpose and key logic of each test, focusing on files and directories with meaningful content.

---

## core/src/main.cpp
- Sets up and runs Google Test suite for core CAN frame logic.
- `addInput`: Creates CAN CC frames, handles edge cases (e.g., DLC > 8), and checks frame validity.
- Uses `testing::InitGoogleTest(&argc, argv)` to initialize and run all tests.

## core/fuzz/src/protocol_frame_fuzz_test.cpp
- Fuzz tests for CAN protocol frame handling.
- Generates frames with all valid data sizes, especially for DLC > 8.
- Ensures byte size is capped at 8 and asserts correct frame value handling.

## isotp/send.py
- Python test for sending CAN messages using the `isotp` library.
- Opens a socket on a virtual CAN interface (`vcan`), sets RX and TX addresses.
- Sends a message that fits into a single CAN frame.

## isotp/canfd.py
- Python test for sending CAN FD messages.
- Specifies arbitration ID and uses SocketCAN on `vcan0` channel.
- Sends messages over the bus using the defined interface.

## linux/socketcan/src/main.cpp
- Entry point for running all SocketCAN-related tests using Google Test.

## linux/socketcan/src/soc_shutdown_test.cpp
- Simulates SoC (State of Charge) shutdown sequence for OrionBMS 2 via SocketCAN and `vcan0`.
- Sets up test suite, simulates SoC from 100% to 0%, sends messages, and checks assertions.
- Detects low battery (18% SoC), triggers shutdown signal to motor controller/inverter.
- Handles shutdown messaging and checks for CAN frame acknowledgements from Sevcon Gen4 controller.

## rp2040/mcp2515/src/main.cpp
- Runs all tests for MCP2515 CAN controller on RP2040 platform.

## rp2040/mcp2515/src/provider_test.cpp
- Sets up provider tests for SPI communication (init, set, read, write).
- Registers raw IRQ handler on current core for testing interrupt handling.

## rp2040/stubs/include/hardware/gpio.stub.h
- Stub for Pico SDK hardware GPIO header.
- Simulates GPIO IRQ levels and pin behavior for host-based tests.

---


### Test Cases Summary

Below is a list of the main test cases covered in this directory:

- **Core CAN Frame Tests**
	- Valid CAN CC frame
	- Valid CAN CC frame (extended ID)
	- Edge-case: DLC above 8 (truncation)
	- Invalid CAN FD remote frame
	- Invalid CC frame with DLC overflow
	- Invalid CC frame with extended ID but no IDE bit
	- Valid CAN FD frame

- **Fuzz Tests**
	- All valid data sizes for CAN CC frames
	- All valid data sizes with DLC above 8

- **ISOTP Python Tests**
	- Single-frame message send/receive

- **CAN FD Python Tests**
	- CAN FD message send with custom arbitration ID and DLC

- **SocketCAN Tests (Linux)**
	- Linear SoC depletion and shutdown trigger simulation
		- Simulates OrionBMS 2 sending SoC from 100% to 0%
		- Detects low battery (≤18%) and sends shutdown signal
		- Sends SDO shutdown command to Sevcon Gen4 motor controller
		- Checks for CAN frame acknowledgement from Sevcon

- **RP2040 MCP2515 Provider Tests**
	- SPI initialization, format, read/write
	- Register raw IRQ handler on current core

- **RP2040 GPIO Stub**
	- Simulates GPIO IRQ levels and pin behavior for host-based tests

---
This summary provides a quick reference to the types of tests implemented in the directory. For details, see the relevant test source files.