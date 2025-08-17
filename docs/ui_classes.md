# UI Classes (Version 1.0.0)

This document details the major user interface (UI) components or classes within the project, describing their purpose, the data they manage or display, and their interaction with the core logic classes.

## Application

*   **Purpose**: The central class responsible for managing the application window, handling user input events, and orchestrating the rendering of the user interface, including the integration of Dear ImGui.
*   **Data Managed/Displayed**:
    *   Application window state (size, open/closed).
    *   Mouse input coordinates (`previousMousePos`).
    *   Current scene selection (`selectedScene`).
    *   Overall application running state (`running`).
*   **Interaction with Logic Classes**:
    *   Initializes and manages the `sf::RenderWindow` (SFML graphics library).
    *   Calls `ListenEvent` to process SFML events, which can trigger actions on `Object`s (e.g., `DetectObjectPress`) or `Scene` transitions (`OnSceneChange`).
    *   Invokes `RenderGameControls` to display UI elements, which likely interact with scene-specific logic or global application settings.
    *   Uses `SetImGuiGlobalSize` to configure the ImGui rendering, which then draws UI elements that can modify properties of `Object`s, `Component`s, or `Scene`s.

## Object

*   **Purpose**: As the base class for all simulation entities, `Object` provides the framework for individual objects to expose their properties and behaviors through a user interface, typically an editor window.
*   **Data Managed/Displayed**:
    *   Object's name (`name`).
    *   Transform properties (position, scale, rotation) via its `Transform` component.
    *   Properties of attached `Component`s.
    *   Internal `edit` flag to control the visibility of its editor window.
*   **Interaction with Logic Classes**:
    *   The `RenderEditorWindow()` method, often called by the `Application` or `Scene`, uses ImGui to create a dedicated UI window for the object.
    *   Within `RenderEditorWindow()`, it iterates through its `components` and calls their `RenderEditor()` methods, allowing each component to expose its own UI controls.
    *   Changes made through the UI (e.g., adjusting `transform` values) directly modify the object's logical state.

## Scene

*   **Purpose**: Each `Scene` manages a specific simulation environment and its associated objects. From a UI perspective, scenes are responsible for rendering their contained objects and potentially providing scene-specific controls or information.
*   **Data Managed/Displayed**:
    *   The list of `Object`s (`objectsList`) within the scene.
    *   The SFML `sf::View` (`view`) used for rendering the scene's content.
    *   (Implicit) Scene-specific simulation parameters that might be exposed via UI.
*   **Interaction with Logic Classes**:
    *   The `Run()` method orchestrates the scene's lifecycle, including calling `Update()` and `Draw()` on its `objectsList`, which in turn renders their visual representations.
    *   Scenes might expose UI elements (via ImGui, potentially through `Application::RenderGameControls` or their own `RenderEditorWindow` if they were `Object`s) to control simulation parameters or add/remove objects, directly affecting the scene's logic.

## Component

*   **Purpose**: `Component`s are modular units of behavior attached to `Object`s. From a UI perspective, they provide a standardized way for individual behaviors or data sets to expose their properties for editing through the ImGui interface.
*   **Data Managed/Displayed**:
    *   Properties specific to the component (e.g., `RigidBody`'s mass, velocity; `Shape`'s color, geometry).
*   **Interaction with Logic Classes**:
    *   The `RenderEditor()` method is the primary UI interface for a component. It uses ImGui functions to create widgets (sliders, input fields, checkboxes) that directly manipulate the component's internal properties.
    *   Changes made through these UI widgets immediately update the component's logical state, affecting the behavior of its owning `Object`.
