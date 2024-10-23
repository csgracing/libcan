# libcan

## Folder structure

- **`core`**

    Core project files not tied to a specific platform
- **`rp2040`**
  - **`rp2040/mcp2515`**

    - **`rp2040/mcp2515/impl`**

        `CANBus` subclass implementation for `mcp2515` on `rp2040` MCU.
    - **`rp2040/mcp2515/standalone`**
      
        Standalone target for testing