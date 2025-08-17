# Features (Version 1.0.0)

This document lists the main features implemented in the codebase, providing a description of each and the primary modules or files responsible for its implementation.

## Acceleration Simulation

*   **Description**: Simulates objects under constant acceleration, demonstrating changes in velocity and position over time.
*   **Responsible Modules/Files**:
    *   `AccellerationScene.h`
    *   `AccellerationScene.cpp`
    *   `Acceleration.cpp`
    *   `Physics.h` (for general physics concepts)

## Bounce Simulation

*   **Description**: Simulates objects bouncing off surfaces, demonstrating elastic and inelastic collisions.
*   **Responsible Modules/Files**:
    *   `BounceSimulationScene.h`
    *   `BounceSimulationScene.cpp`
    *   `Physics.h` (for collision detection and resolution)

## Energy Conservation (Billiard)

*   **Description**: Demonstrates the principle of energy conservation through a billiard-like simulation, focusing on kinetic and potential energy transformations.
*   **Responsible Modules/Files**:
    *   `EnergyConservationScene.h`
    *   `EnergyConservationScene.cpp`
    *   `EnergyConservationBilliard.h`
    *   `EnergyConservationSceneBilliard.cpp`
    *   `Physics.h`

## Gravity Simulation

*   **Description**: Simulates objects under the influence of gravitational forces, demonstrating orbital mechanics or free fall.
*   **Responsible Modules/Files**:
    *   `GravitySimulationScene.h`
    *   `GravitySimulationScene.cpp`
    *   `ForceField.cpp` (if gravity is implemented as a force field)
    *   `Physics.h`

## Object Management

*   **Description**: Provides a flexible system for creating, updating, rendering, and managing various entities within the simulation.
*   **Responsible Modules/Files**:
    *   `Object.h`
    *   `Object.cpp`
    *   `Component.h` (for attaching behaviors)
    *   `Transform.h` (for position, scale, rotation)

## Pendulum Simulation

*   **Description**: Simulates the motion of a pendulum, demonstrating oscillatory behavior under gravity.
*   **Responsible Modules/Files**:
    *   `PendulumScene.h`
    *   `PendulumScene.cpp`
    *   `Pendulum.h`
    *   `Pendulum.cpp`
    *   `Physics.h`

## UI Editing and Debugging

*   **Description**: Provides in-application tools for modifying object properties, scene parameters, and debugging simulation behavior in real-time.
*   **Responsible Modules/Files**:
    *   `imgui/` (Dear ImGui library)
    *   `imgui-SFML.h`
    *   `imgui-SFML.cpp`
    *   `Application.h` (for UI rendering and event handling)
    *   `Object.h` (for `RenderEditorWindow`)
    *   `Component.h` (for `RenderEditor`)
