# libcan

**libcan** is a work-in-progress, MCU-agnostic CAN (Controller Area Network) library developed by CSG Racing as a learning exercise. Its main goal is to provide a reusable, modular, and portable codebase for handling CAN bus communication across different microcontroller platforms.

> **Note:** This project is under active development. Features, APIs, and structure are subject to change.

## Features

- **MCU-Agnostic Design:** Abstracts hardware-specific details for portability.
- **Modular Structure:** Easy to extend for different MCUs and CAN controllers.
- **CMake-Based Build System:** Simplifies integration in modern C++ projects.
- **Learning Focus:** Serves as a reference for students and developers interested in CAN bus implementation.

## Project Structure

The repository is organized as follows:

```
.
├── .github/          # GitHub configuration files (workflows, issue templates, etc.)
├── .gitignore        # Git ignore rules
├── .gitmodules       # Git submodule configuration
├── .vscode/          # VS Code project settings
├── CMakeLists.txt    # Main CMake build script
├── CMakePresets.json # CMake configuration presets
├── README.md         # This documentation file
├── docs/             # Project documentation (design notes, usage, etc.)
├── lib/              # External libraries (submodules or third-party code)
├── src/              # Source code for the CAN library
├── standalone/       # Standalone examples or demo applications
└── test/             # Unit and integration tests for the library
```

### Key Directories

- **src/**: Contains all core source files for the CAN library, including hardware abstraction and protocol logic.
- **lib/**: Houses external libraries or dependencies, managed as submodules.
- **test/**: Contains tests to validate the correctness and robustness of the library.
- **standalone/**: Example or demonstration projects showing how to use libcan independently or on different platforms.
- **docs/**: Additional documentation, design references, and usage guides.

## Getting Started

### Prerequisites

- **C++ Compiler:** Compatible with C++17 or newer.
- **CMake:** Version 3.15 or later recommended.
- **Supported MCU SDK:** (Dependent on your target hardware & board support)
- (Optional) **Visual Studio Code:** Project includes VS Code settings.

### Building the Library

1. **Clone the repository**
   ```sh
   git clone --recurse-submodules https://github.com/csgracing/libcan.git
   cd libcan
   ```

2. **Configure the build with CMake**
   ```sh
   cmake -S . -B build
   ```

3. **Build**
   ```sh
   cmake --build build
   ```

### Running Tests

Tests are located in the `test/` directory. You can build and run them using CMake:

```sh
cmake -S . -B build -DBUILD_TESTING=ON
cmake --build build
cd build && ctest
```

### Example Usage

Example applications are available under the `standalone/` directory. These demonstrate how to initialize and use the CAN library in typical scenarios. Refer to the documentation in `docs/` and the code comments for guidance.

## Contributing

Contributions are welcome! Please open issues for bugs, feature requests, or questions. Pull requests should follow the repository’s style and include relevant tests.

## License

This project currently does not specify a license. Please contact the maintainers if you wish to use the code in commercial or open projects.

## Links

- [CSG Racing on GitHub](https://github.com/csgracing)
- [Project Repository](https://github.com/csgracing/libcan)

---