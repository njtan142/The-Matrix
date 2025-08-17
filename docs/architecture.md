# Architecture (Version 1.0.0)

This document provides a high-level overview of the system's architecture, describing its design patterns, frameworks, and key architectural decisions.

## Overview

The project is a desktop application developed in C++ that simulates various physics phenomena. It follows a component-based architecture for its simulation entities and utilizes external libraries for graphics rendering and user interface.

## Architectural Patterns

*   **Component-Based Architecture**: Core simulation entities (`Object`s) are designed to be flexible and extensible through the attachment of various `Component`s (e.g., `Rigidbody`, `Shape`, `Transform`, `ForceField`). This promotes modularity and reusability of behaviors.
*   **Scene Management**: The application uses a scene-based approach (`Scene` class and its derivatives) to organize and manage different simulation environments. Each scene encapsulates its own set of objects and simulation logic.

## Key Technologies and Frameworks

*   **C++**: The primary programming language for the entire application.
*   **SFML (Simple and Fast Multimedia Library)**: Used for:
    *   **Graphics**: Rendering 2D shapes, managing windows, and handling visual output.
    *   **Windowing**: Creating and managing the application window.
    *   **Event Handling**: Processing user input (mouse, keyboard).
*   **Dear ImGui**: A bloat-free graphical user interface library used for creating interactive debugging tools and in-application editors. It provides immediate mode GUI functionality, allowing for dynamic UI elements to control simulation parameters and object properties.

## Communication Between Components

Communication within the application is primarily through direct function calls and object references within the C++ codebase.

*   **Application to Scene**: The `Application` class manages the active `Scene` and calls its `UpdateAndRender()` method to execute the scene's logic and rendering loop.
*   **Scene to Objects**: A `Scene` iterates through its `objectsList` and calls their `Update()` and `Draw()` methods, delegating simulation and rendering responsibilities to individual objects.
*   **Objects to Components**: `Object`s interact with their attached `Component`s through direct method calls (e.g., `GetComponent<T>()`, `AddComponent<T>()`). Components, in turn, operate on the `Object`'s data (e.g., `Transform` component modifies the object's position).
*   **UI Interaction**: ImGui-based UI elements directly manipulate the properties of `Object`s and `Component`s. This is achieved by calling `RenderEditorWindow()` on `Object`s and `RenderEditor()` on `Component`s, which then use ImGui widgets to modify the underlying C++ data.

## High-Level Block Diagram

```
+-------------------+       +-------------------+       +-------------------+
|                   |       |                   |       |                   |
|    User Input     |------>|    Application    |<----->|       SFML        |
| (Keyboard, Mouse) |       | (Window, Events)  |       | (Graphics, Window)|
|                   |       |                   |       |                   |
+-------------------+       +-------------------+       +-------------------+
          ^                           |                           ^
          |                           |                           |
          |                     (Manages Scenes)                  |
          |                           |                           |
+-------------------+       +-------------------+       +-------------------+
|                   |       |                   |       |                   |
|    Dear ImGui     |<----->|       Scene       |<----->|    Simulation     |
| (UI Rendering,    |       | (Object Mgmt,     |       |     Objects       |
|  Editor Controls) |       |  Physics Loop)    |       | (Object, Rigidbody,|
|                   |       |                   |       |  Shape, Transform) |
+-------------------+       +-------------------+       +-------------------+
```
