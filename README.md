# ImguiAddon

[![CMake on multiple platforms](https://github.com/Icey1717/ImguiAddon/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/Icey1717/ImguiAddon/actions/workflows/cmake-multi-platform.yml)

**ImguiAddon** is a lightweight C++ library that provides a simple API for running an ImGui-powered window on its own thread. Designed for seamless integration into your projects, it supports customizable frame rates, dynamic window sizing, and user-defined rendering logic.

## Features

- **Multi-threaded ImGui rendering**: The ImGui window runs independently of your main application logic.
- **Simple API**: Create and configure a window with minimal boilerplate.
- **Custom update callback**: Define your ImGui content using an easy-to-implement callback function.
- **Adjustable frame rate**: Control the target frame rate for smooth rendering.

## Getting Started

### Prerequisites

- A C++17-compliant compiler.
- [CMake](https://cmake.org/) for building the library.
- The following libraries (auto-downloaded via CMake):
  - [GLFW](https://www.glfw.org/)
  - [ImGui](https://github.com/ocornut/imgui)

### Installation

Clone the repository and configure the project using CMake:

```bash
git clone https://github.com/yourusername/ImguiAddon.git
cd ImguiAddon
mkdir build && cd build
cmake ..
cmake --build .
```

## Example Usage

Here’s a basic example demonstrating how to create a window and render ImGui content using `ImguiAddon`:

```cpp
#include "ImguiAddon.h"
#include <imgui.h>

// Define the ImGui update callback
static void Update() {
    // Example ImGui content
    ImGui::Begin("Hello, Multithreading!");
    ImGui::Text("This window is running on its own thread.");
    ImGui::End();
}

int main() {
    // Create the ImGui window
    ImguiAddon::Window window{ {1200, 800, 60, "Demo Window"}, Update };

    // Main application loop
    while (true) {
        // Your main application logic here
    }

    return 0;
}
```
