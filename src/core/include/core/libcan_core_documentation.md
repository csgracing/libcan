# libcan/src/core/include/core README

This README provides an overview of the header files in the `libcan/src/core/include/core` folder. This library implements CAN bus communication with ISO-TP transport for sending messages longer than 8 bytes. The flow is: hardware → CAN frames → ISO-TP reassembly → complete messages.

---

## providers/base.h
- Hardware interface that talks to actual CAN controllers (MCP2515, built-in CAN, etc.)
- Implement `readMessage()`, `hasMessage()`, `sendMessage()` for specific hardware
- Provides thread-safe queuing so multiple threads can send/receive without conflicts
- Entry point where raw CAN data enters the system

## protocol/frame/identifier.h
- Handles CAN message addresses (who sent it, who should receive it)
- Splits 29-bit extended IDs into 11-bit base + 18-bit extended parts for easier processing
- Provides hash function so you can use CAN IDs as keys in lookup tables
- Critical for routing - every message needs to know where it came from and where it's going

## protocol/frame/data.h
- Defines the three key bits in every CAN frame header
- RTR bit: is this a data frame or a request for data?
- IDE bit: is this using 11-bit or 29-bit addressing?
- EDL bit: is this old CAN (8 bytes max) or new CAN FD (64 bytes max)?
- These bits determine how to interpret the rest of the frame

## protocol/frame/dlc.h
- Translates "data length code" to actual byte count
- CAN Classic: DLC 0-8 means 0-8 bytes
- CAN FD: DLC 9-15 means 12,16,20,24,32,48,64 bytes
- Lookup table handles the conversion automatically

## protocol/frame/type.h
- Classifies frames into categories: CAN Classic vs CAN FD, standard vs extended addressing
- Uses bitfield encoding to pack multiple flags into one enum value
- Helps other parts of the system quickly determine "what kind of frame is this?"
- Prevents processing CAN FD frames with CAN Classic logic (which would break)

## protocol/frame/frame.h
- Main CAN frame structure that everything else uses
- Union allows accessing data as bytes or 32-bit words for efficiency
- Separate pointer for CAN FD data (since it can be much larger)
- `create()` function validates raw hardware data and builds proper frame structure
- This is what flows through the entire system after leaving the hardware layer

## protocol/frame/util.h
- Helper functions that analyze frames and make decisions
- `determineType()`: looks at IDE/EDL bits to classify the frame
- `determineDataSize()`: figures out actual payload length from DLC
- `determineIfExtendedFormat()`: checks if frame uses 29-bit addressing
- Used throughout the system to avoid duplicating frame analysis logic

## isotp/link/state.h
- State machine for ISO-TP connections
- IDLE: ready to start new message
- IN_PROGRESS: currently receiving/sending multi-frame message
- FULL: receive buffer is full, need to process before accepting more
- ERROR: something went wrong, connection needs reset
- Prevents mixing up pieces of different messages

## isotp/link/directional_link.h
- Manages one direction of communication (either sending OR receiving)
- Allocates buffers for reassembling multi-frame messages
- Tracks sequence numbers to ensure frames arrive in correct order
- `copyIntoBuffer()` appends incoming data to the growing message
- Each ISO-TP connection needs two of these (one for each direction)

## isotp/link/link.h
- Complete bidirectional ISO-TP connection
- Combines send + receive directional links
- Has message queue for completed messages waiting to be processed
- Created with TX and RX CAN IDs (usually consecutive, like 0x123 and 0x124)
- This is what application code interacts with to send/receive long messages

## isotp/link/manager.h
- Manages multiple ISO-TP connections simultaneously
- Hash table maps CAN IDs to their corresponding links
- `handle_receive()` is the main entry point - receives CAN frame, routes to correct link
- Allows one application to talk to multiple ECUs at the same time
- Central dispatcher that makes routing decisions

## isotp/tl/pci/frame_type.h
- Identifies what kind of ISO-TP frame this is by reading first 4 bits of data
- Single frame: complete message fits in one CAN frame
- First frame: starts a multi-frame message, contains total length
- Consecutive frame: continuation of multi-frame message, has sequence number
- Flow control: receiver telling sender "keep going", "wait", or "stop"
- Every ISO-TP frame processing decision starts here

## isotp/tl/pci/single_frame.h
- Data length encoding for single-frame messages
- CAN Classic: 1-7 bytes (0 is reserved, 8 would need multiple frames)
- Length stored in lower 4 bits of first data byte
- Simplest case - entire message fits in one CAN frame, no reassembly needed

## isotp/tl/pci/consecutive_frame.h
- Sequence number management for multi-frame messages
- 4-bit counter (0-15) that increments with each frame
- `precedes()` checks if this frame comes right after the previous one
- Wraps from 15 back to 0 when it overflows
- Detects missing, duplicate, or out-of-order frames

## isotp/tl/pci/flow_control.h
- Receiver's way of controlling message flow
- CONTINUE_TO_SEND: "send next batch of frames"
- WAIT: "pause, I'm busy processing"
- OVERFLOW: "stop, my buffer is full"
- Prevents fast senders from overwhelming slow receivers
- Critical for reliable multi-frame delivery

## isotp/tl/handler/base.h
- Abstract base class that all frame processors inherit from
- `handle()` method takes a CAN frame and ISO-TP link, processes the frame
- Returns success/error code indicating what happened
- Template for implementing the four different frame type handlers

## isotp/tl/handler/single_frame.h
- Processes complete messages that fit in one CAN frame
- Extracts payload length from PCI, validates it against CAN frame size
- Copies payload directly to application without buffering
- Fastest path through the system - no state machine complexity

## isotp/tl/handler/first_frame.h
- Handles the start of multi-frame messages
- Reads total message length from frame, allocates receive buffer
- Sets link state to IN_PROGRESS
- May send flow control frame to tell sender "ready for more frames"
- Initializes the multi-frame reception process

## isotp/tl/handler/consecutive_frame.h
- Processes frames 2, 3, 4... of multi-frame messages
- Validates sequence number matches what we expect
- Appends payload to growing message buffer
- Checks if message is now complete
- May send flow control frames to manage sender timing

## isotp/tl/handler/manager.h
- Routes incoming frames to the correct handler based on frame type
- Hash table maps frame types to handler instances
- `handle()` method is called by link manager for each received frame
- Central dispatch point that implements the ISO-TP state machine

## isotp/tl/pdu/base.h
- Base class for outgoing message builders
- `createPayload()` method builds the actual bytes to send over CAN
- Each PDU type implements this differently based on ISO-TP frame format
- Used when creating messages to send (vs processing received messages)

## isotp/tl/pdu/flow_control.h
- Builds flow control frames to send
- Combines flow status, block size, and separation time into proper byte format
- Used when receiver needs to control sender's transmission rate
- Implements the "sender" side of flow control protocol

## logger.h
- Singleton logger that all parts of the system can use
- Thread-safe so multiple CAN links can log simultaneously without corruption
- Custom formatter removes timestamps (assumes external logging handles that)
- Central logging point for debugging CAN communication issues

## logger_defines.h
- Conditional compilation macros for different log levels
- TRACE: detailed frame-by-frame analysis with hex dumps
- DEBUG: state changes, buffer allocations, sequence tracking
- INFO: connection establishment, message completion
- WARN/ERROR: problems that need attention
- Unused log levels compile to nothing for performance

## isotp/error/common/category/libcan.h
- Base error category for the entire library
- Provides standard error handling interface using Boost.System
- Parent class that ISO-TP specific errors inherit from
- Allows integrating libcan errors with larger applications using Boost

## isotp/error/common/category/isotp.h
- ISO-TP specific error category
- Inherits from libcan base, adds transport layer context
- Used by all ISO-TP related error codes
- Provides meaningful error names like "isotp" instead of generic "libcan"

## isotp/error/code/category/isotp_code.h
- Specific error category for ISO-TP error codes (vs conditions)
- Maps error numbers to human-readable messages
- `default_error_condition()` groups related errors for easier handling
- Used when you need specific error details, not just general categories

## isotp/error/condition/category/isotp_condition.h
- Error category for high-level error conditions
- Groups related error codes into broader categories
- Used when you want to catch "any frame processing error" vs specific errors
- Simplifies error handling for applications that don't need fine detail

## isotp/error/common/overload.h
- C++ utility for handling variant error types
- Allows writing visitor functions that handle different error categories
- Technical helper that makes error handling code cleaner
- Used internally by error processing, not directly by applications

## isotp/error/code/success.h
- Success status code (0) indicating operation completed normally
- Part of Boost.System error handling - need explicit success type
- Used throughout the system to indicate "no error occurred"
- Allows consistent error handling patterns

## isotp/error/code/single_frame.h
- Specific errors that occur when processing single-frame messages
- CAN Classic vs CAN FD validation problems
- Payload length mismatches between PCI and actual data
- DLC validation errors (frame claims wrong data length)
- Reserved field violations
- Unknown frame formats

## isotp/error/code/first_frame.h
- Errors specific to first frames of multi-frame messages
- Currently only handles unexpected signaling errors
- Will expand as more first-frame validation is added
- Used when message length or format is invalid

## isotp/error/code/consecutive_frame.h
- Errors during multi-frame message reassembly
- Link state mismatch: got consecutive frame but we're not expecting one
- Sequence number mismatch: frame 5 arrived but we expected frame 3
- Payload too long: frame has more data than remaining message space
- Critical for detecting corrupted or missing frames

## isotp/error/code/frame_handle.h
- Errors when no handler exists for a frame type
- Happens if frame type field contains invalid value (not 0-3)
- Could indicate corrupted frame or unsupported ISO-TP extension
- System doesn't know how to process this frame

## isotp/error/code/link_manager.h
- Errors in link management
- Main error: received frame for CAN ID that's not registered
- Prevents processing random frames that aren't part of active connections
- Security feature - only process frames from known sources

## isotp/error/code/code.h
- Master list combining all error types into single interface
- `Code` struct allows using any error enum value
- Lookup table maps error codes to descriptive messages
- Central registry for all possible error conditions

## isotp/error/condition/condition.h
- High-level error conditions that group related error codes
- Used when you want to catch broad categories vs specific errors
- Simplifies application error handling

## isotp/error/condition/frame_condition.h
- Three broad categories of frame processing results
- IGNORED: frame was valid but not relevant (wrong CAN ID, etc.)
- INVALID: frame was malformed or violated protocol
- UNKNOWN: frame type not recognized
- Used for general error classification and reporting

---

### System Flow

1. **Hardware** (`providers/base.h`) receives raw CAN data
2. **Frame Processing** (`protocol/frame/*`) validates and structures the data  
3. **Link Management** (`isotp/link/manager.h`) routes frames to correct ISO-TP connections
4. **Frame Handlers** (`isotp/tl/handler/*`) process frames based on type (single/first/consecutive/flow control)
5. **Message Assembly** happens in directional links with proper error handling
6. **Complete Messages** are queued for application processing

### Summary

This directory contains **37 header files** implementing a complete CAN + ISO-TP stack:

- **CAN Protocol (7 files)**: Low-level frame handling, addressing, type detection
- **ISO-TP Links (4 files)**: Multi-frame message assembly with state management  
- **Frame Handlers (5 files)**: Process different ISO-TP frame types
- **Protocol Control (4 files)**: Sequence numbers, flow control, frame classification
- **Error System (15 files)**: Comprehensive error handling with Boost integration
- **Hardware Interface (1 file)**: Abstract layer for CAN controllers
- **Utilities (1 file)**: Logging system

**Use Cases**: Automotive diagnostics (UDS), industrial protocols, any system needing reliable delivery of messages >8 bytes over CAN bus.