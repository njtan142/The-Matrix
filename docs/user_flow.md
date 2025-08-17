# User Flow (Version 1.0.0)

This document describes a key user journey within the application, detailing user actions, system responses, and the relevant components involved at each stage.

## Main Application Flow: Simulation Selection and Execution

This flow describes how a user launches the application, selects a physics simulation scene, and interacts with it.

1.  **User Action**: Launches the application executable.
    *   **System Response**: The application initializes, creates a rendering window, and sets up the main application loop.
    *   **Relevant Components**:
        *   `main.cpp`: Contains the `main` function, the entry point of the program.
        *   `Application.h`/`Application.cpp`: Manages the application window, event handling, and scene management.
        *   `SFML.sln`, `SFML.vcxproj`: Project configuration files for building the executable.

2.  **User Action**: (Implicit) The application presents a user interface (likely via ImGui) to select a simulation scene.
    *   **System Response**: The application renders the initial UI, allowing the user to choose from available scenes.
    *   **Relevant Components**:
        *   `Application.h`/`Application.cpp`: Responsible for rendering the UI and handling UI events.
        *   `imgui/`: Dear ImGui library files, providing UI elements.
        *   `imgui-SFML.h`/`imgui-SFML.cpp`: Integration layer between ImGui and SFML.

3.  **User Action**: Selects a specific simulation scene (e.g., "Gravity Simulation").
    *   **System Response**: The application loads and initializes the chosen scene, preparing it for rendering and simulation.
    *   **Relevant Components**:
        *   `Application.h`/`Application.cpp`: Manages the active scene and transitions.
        *   `Scene.h`/`Scene.cpp`: Base class for all simulation scenes, defining common interfaces.
        *   Specific scene files (e.g., `GravitySimulationScene.h`/`GravitySimulationScene.cpp`): Implement the logic and rendering for the selected simulation.

4.  **User Action**: Observes and potentially interacts with the running simulation (e.g., adjusts parameters, adds/removes objects).
    *   **System Response**: The application continuously updates the simulation state based on physics logic, renders objects, and responds to user input within the scene.
    *   **Relevant Components**:
        *   Specific scene files (e.g., `GravitySimulationScene.h`/`GravitySimulationScene.cpp`): Contain the simulation-specific update and rendering logic.
        *   `Object.h`/`Object.cpp`: Base class for all simulated objects.
        *   `Rigidbody.h`/`Rigidbody.cpp`: Handles physics properties of objects.
        *   `Shape.h`/`Shape.cpp`, `Circle.h`/`Circle.cpp`, `Rectangle.h`/`Rectangle.cpp`: Define the visual and physical properties of shapes.
        *   `Vector2.h`/`Vector2.cpp`: Provides 2D vector mathematics for physics calculations.
        *   `Physics.h`: Defines global physics constants and utility functions.
        *   `Camera.h`/`Camera.cpp`: Controls the view of the simulation.
        *   `ForceField.cpp`: Implements forces affecting objects.

5.  **User Action**: Closes the application window.
    *   **System Response**: The application gracefully shuts down, releasing resources.
    *   **Relevant Components**:
        *   `Application.h`/`Application.cpp`: Handles application shutdown and resource cleanup.
