# Project Overview

This project, named "The Matrix" (SFML-ImGUI), is a C++ application designed for simulating various physics phenomena. It leverages the SFML (Simple and Fast Multimedia Library) for graphics rendering and ImGui for creating an interactive user interface. Users can select and observe different physics simulations, such as energy conservation, bounce simulations, gravity, pendulum motion, and acceleration. The project employs a component-based architecture for its in-scene objects, allowing for flexible and modular physics interactions.

## Key Features:
*   **Interactive Physics Simulations:** Explore different physics scenarios through a user-friendly interface.
*   **SFML Graphics:** Utilizes SFML for efficient 2D rendering of simulation elements.
*   **ImGui Integration:** Provides in-application controls and object property editors for real-time adjustments.
*   **Component-Based Object System:** Objects in the simulation are built using a flexible component system (e.g., Transform, RigidBody, Shape).

## Core Components:
*   `Application.h`/`Application.cpp`: Manages the main application loop, window handling, event processing, and scene switching.
*   `Scene.h`: An abstract base class for all simulation scenes, defining the interface for scene initialization, running, and unloading.
*   `Object.h`: The base class for all interactive elements within a scene, supporting a component-based design.
*   `Physics.h`: Defines core physics components like `RigidBody` (for physical properties) and `ForceField` (for external forces).
*   `Vector2.h`: A custom 2D vector implementation used for all vector mathematics in the physics engine.

# Building and Running

This project is configured as a Visual Studio project.

## Prerequisites:
*   Visual Studio (2019 or newer recommended)
*   SFML libraries (included in `libraries/` directory)
*   ImGui libraries (included in `imgui/` directory)

## Steps to Build and Run:

1.  **Open the Solution:** Open the `SFML.sln` file in Visual Studio.
2.  **Select Configuration:** Choose your desired build configuration (e.g., `Debug` or `Release`) and platform (e.g., `x64` or `Win32`) from the Visual Studio toolbar.
3.  **Build the Project:** Go to `Build > Build Solution` or press `F7`.
4.  **Run the Application:** Go to `Debug > Start Debugging` or press `F5`.

Alternatively, you can build from the command line using MSBuild:

```bash
# For Debug x64
msbuild SFML.vcxproj /p:Configuration=Debug /p:Platform=x64

# For Release x64
msbuild SFML.vcxproj /p:Configuration=Release /p:Platform=x64
```

After building, the executable will be located in the `Debug` or `Release` folder within the project directory.

# Development Conventions

*   **Language:** C++
*   **Graphics:** SFML
*   **UI:** ImGui
*   **Object Architecture:** Component-based design for in-scene objects.
*   **Code Style:** Follows standard C++ practices. Indentation and formatting should align with existing codebase.
*   **Scene Management:** New physics simulations should be implemented as new `Scene` derived classes.
*   **Object Interaction:** Objects can be selected and their properties edited via ImGui windows.
