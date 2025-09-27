# Core Directory Documentation

This directory contains the core components and functionalities of the project. It includes essential modules, utilities, and services that form the backbone of the application.

## Directory Structure

```
core/
├── include/          # Header files for core components
├── src/              # Source files for core components
├── tests/            # Unit and integration tests for core components
├── CMakeLists.txt    # CMake build script for the core module
└── README.md         # Documentation for the core module
```

### Key Directories
- **include/**: Contains public header files that define the interfaces for the core components.
- **src/**: Contains the implementation of the core components.

## ISOTP

The ISOTP (ISO 15765-2) protocol is implemented in the `isotp` directory. This protocol is used for sending and receiving large messages over CAN by breaking them into smaller frames.

### ISOTP Directory Structure

```isotp/
├── error/             # Header files for ISOTP components
├── common/            # Source files for ISOTP components
├── condition/         # Unit and integration tests for ISOTP co
```

### ../error

The `code` directory contains definitions and implementations related to error handling within the ISOTP protocol. This includes error codes, exceptions, and mechanisms for reporting and managing errors that occur during ISOTP communication.

#### ../error/code

Uses a mapping of error codes to human-readable strings. Error code are from the ISO 15765-2 specification.

#### ../error/common

Contains common utilities and definitions used across the ISOTP Error handling components. This may include shared constants, helper functions, and base classes that facilitate error management in the ISOTP protocol.

#### ../error/condition

Defines specific conditions and scenarios under which errors may occur in ISOTP communication. This includes classes and functions that represent various error states, allowing for structured handling and reporting of these conditions during protocol operations.mponents

### ../link

The `link` directory contains definitions and implementations related to the data link layer of the ISOTP protocol. This includes mechanisms for framing, addressing, and managing the transmission of data over the CAN bus.

The primary purpose of this protocol is to facilitate the transfer of data payloads that are larger than the standard 8-byte limit of a single CAN frame. It achieves this by segmenting large messages into multiple frames on the sender's side and reassembling them on the receiver's side.

#### ../tl

The `tl` (Transport Layer) directory contains the implementation of the ISO-TP transport layer logic. This layer is responsible for segmenting large messages into multiple CAN frames for transmission and reassembling them upon reception.

### Responsibilities

- **Segmentation:** Splits large data payloads into smaller frames that fit within the CAN frame size limit.
- **Reassembly:** Collects and reconstructs segmented frames into the original message on the receiving side.
- **Protocol Control Information (PCI):** Handles the creation and parsing of PCI fields, such as sequence numbers and frame types (Single Frame, First Frame, Consecutive Frame, Flow Control).
- **Flow Control:** Manages flow control frames to coordinate data transfer between sender and receiver.

### ../protocol/frame

The `frame` directory contains definitions and implementations related to the framing of data in the ISOTP protocol. This includes the structure and handling of different types of frames used in ISOTP communication.

- ***`dlc.cpp`*** defines mappings between data length codes (DLC) and actual byte lengths, which is crucial for interpreting CAN frames correctly.

- ***`frame.cpp`*** constructs and returns a frame, or a nullopt if invalid format.

- ***`util.cpp`*** contains util functions such as getType() or getSize().


### ../providers

- ***`base.cpp`*** provides basic frame creation, queuing, and message handling for CAN bus communication.

### logger.cpp

- ***`logger.cpp`*** implements logging functionality for the ISOTP protocol, allowing for tracking and debugging of protocol operations and events.