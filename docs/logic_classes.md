# Logic Classes (Version 1.0.0)

This document provides a detailed breakdown of the core business logic classes within the project, including their roles, properties, and methods.

## Acceleration

*   **Description**: Represents a 2D acceleration vector with a direction and magnitude.
*   **Properties**:
    *   `direction`: `Vector2` - The direction of the acceleration.
    *   `magnitude`: `float` - The magnitude of the acceleration.
*   **Methods**:
    *   `Acceleration()`: Default constructor.
    *   `Acceleration(float dx, float dy, float magnitude)`: Constructor to create an acceleration with specified direction components and magnitude.

## Application

*   **Description**: Manages the main application window, event handling, and scene transitions. It acts as the central hub for the application's lifecycle.
*   **Properties**:
    *   `previousMousePos`: `sf::Vector2i` - Stores the previous mouse position for input tracking.
    *   `running`: `bool` - Indicates whether the application is currently running.
    *   `scene`: `Scene*` - Pointer to the currently active scene.
    *   `selectedScene`: `Scenes` - An enum representing the currently selected scene type.
    *   `window`: `sf::RenderWindow` - The main rendering window of the application.
*   **Methods**:
    *   `DetectObjectPress(const sf::Event& event, const std::list<Object*>* objectsList)`: Detects if an object was pressed based on a mouse event.
    *   `InitializeWindow()`: `sf::View*` - Initializes the SFML rendering window and returns a pointer to the default view.
    *   `ListenEvent(sf::View* view, std::list<Object*>* objectsList)`: Listens for and processes SFML events, such as mouse clicks, keyboard input, and window resizing.
    *   `OnMouseMove(sf::RenderWindow& window, sf::View* view)`: Handles mouse movement events, potentially updating the view or interacting with objects.
    *   `OnMousePress(sf::Event& event, std::list<Object*>* objectsList)`: Handles mouse press events, typically for object selection or interaction.
    *   `OnResize(sf::RenderWindow& window, sf::View* view, const sf::Event& event)`: Handles window resize events, adjusting the view accordingly.
    *   `OnSceneChange()`: Manages the transition between different scenes.
    *   `RenderGameControls(sf::View& view)`: Renders in-game controls or UI elements.
    *   `SetImGuiGlobalSize(float scale, float fontSize)`: Sets the global scaling and font size for ImGui UI elements.

## Camera

*   **Description**: Represents a camera within the simulation environment, controlling the view of the scene. It can follow a target object.
*   **Properties**:
    *   `followTarget`: `Object*` - A pointer to the object the camera is currently following. Null if not following any object.
    *   `position`: `Transform` - The transform (position, rotation, scale) of the camera.
    *   `view`: `sf::View*` - A pointer to the SFML view object managed by the camera.
*   **Methods**:
    *   `Camera()`: Default constructor for the Camera class.
    *   `Camera(sf::View view)`: Constructor that initializes the camera with a given SFML view.
    *   `Follow()`: Updates the camera's position to follow its `followTarget` if one is set.

## Circle

*   **Description**: Represents a circular shape in the simulation, inheriting from `Object` and `Shape`.
*   **Properties**:
    *   (Inherits properties from `Object` and `Shape`)
*   **Methods**:
    *   `Circle(const float width, const float height, const float x, const float y, const std::string& name)`: Constructor to create a circle with specified dimensions, position, and name.
    *   `Draw()`: `void` - Draws the circle on the application window.
    *   `RenderEditorWindow()`: `void` - Renders the editor window for the circle.
    *   `Update()`: `void` - Updates the circle's visual properties based on its transform.

## Color

*   **Description**: A utility class for representing and manipulating colors, providing conversions to SFML's `sf::Color` and array representation.
*   **Properties**:
    *   `a`: `const float*` - Pointer to the alpha component of the color.
    *   `b`: `const float*` - Pointer to the blue component of the color.
    *   `g`: `const float*` - Pointer to the green component of the color.
    *   `r`: `const float*` - Pointer to the red component of the color.
    *   `arr`: `float[4]` - Private array storing the RGBA components of the color.
*   **Methods**:
    *   `Array()`: `float*` - Returns a pointer to the internal float array representing the RGBA components.
    *   `Color()`: Default constructor, initializes to a default color (likely black or white).
    *   `Color(const float r, const float g, const float b)`: Constructor to create an opaque color with specified RGB components.
    *   `Color(const float a, const float r, const float g, const float b)`: Constructor to create a color with specified RGBA components.
    *   `toSFC()`: `sf::Color` - Converts the Color object to an SFML `sf::Color` object.

## Component

*   **Description**: Base class for components that can be attached to `Object` instances, providing modular behavior.
*   **Properties**:
    *   `entity`: `Object*` - A pointer to the `Object` this component is attached to.
*   **Methods**:
    *   `Component()`: Default constructor.
    *   `Component(Object* entity)`: Constructor that initializes the component with its owning entity.
    *   `RenderEditor()`: `virtual void` - Renders editor UI for the component (e.g., using ImGui).
    *   `~Component()`: Virtual destructor for proper cleanup of derived components.

## DualShape

*   **Description**: Represents a shape composed of two distinct SFML shapes, inheriting from `Shape`.
*   **Properties**:
    *   `geometry2`: `Vector2` - Represents the dimensions or radius of the second shape.
    *   `xGeometry2`: `std::string` - String description for the x-dimension of the second shape's geometry.
    *   `yGeometry2`: `std::string` - String description for the y-dimension of the second shape's geometry.
    *   (Inherits properties from `Shape`)
*   **Methods**:
    *   `DualShape(Object* entity)`: Constructor that initializes the dual shape with its owning entity.
    *   `DualShape(sf::Shape* first_shape, sf::Shape* second_shape, const std::string& xGeometry, const std::string& yGeometry, const std::string& xGeometry2, const std::string& yGeometry2, const Vector2* geometry, const Vector2* geometry2, Object* entity)`: Constructor to create a dual shape with two SFML shapes, geometry descriptions, and its owning entity.
    *   `Get2()`: `sf::Shape*` - Returns a pointer to the second SFML shape object.

## EnergyConservationSceneBilliard

*   **Description**: A scene class specifically designed to demonstrate energy conservation principles using a billiard simulation.
*   **Properties**:
    *   (Inherits properties from `Scene`)
*   **Methods**:
    *   `EnergyConservationSceneBilliard(sf::View* view)`: Constructor that initializes the scene with a given SFML view.
    *   `InitializeObjects()`: `void` - Overrides the base `Scene` method to initialize objects specific to the billiard energy conservation simulation.

## ForceField

*   **Description**: Represents a force field that can apply forces to `RigidBody` objects within its radius.
*   **Properties**:
    *   `body`: `RigidBody*` - A pointer to the `RigidBody` component of the owning entity.
    *   `magnitude`: `float` - The strength of the force field.
    *   `net_force`: `Vector2` - The calculated net force applied by the force field.
    *   `radius`: `float` - The effective radius of the force field.
*   **Methods**:
    *   `ForceField()`: Default constructor.
    *   `ForceField(Object* entity)`: Constructor that initializes the force field with its owning entity.
    *   `RenderEditor()`: `void` - Renders editor UI for the force field.
    *   `Update(std::list<Object*>* objectsList, float deltaTime)`: Updates the force field's effect on other objects in the scene.

## Object

*   **Description**: Base class for all entities in the simulation, providing common functionalities like component management, transformation, and editor rendering.
*   **Properties**:
    *   `components`: `std::vector<Component*>` - A list of components attached to this object.
    *   `edit`: `bool` - Internal flag indicating if the object's editor window is open.
    *   `name`: `std::string` - The name of the object.
    *   `transform`: `Transform*` - A pointer to the object's transformation data (position, rotation, scale).
*   **Methods**:
    *   `AddComponent()`: `template<typename T> T*` - Adds a component of type `T` to the object. If a component of that type already exists, it returns the existing one.
    *   `AddComponent(T* component)`: `template<typename T> T*` - Adds an existing component of type `T` to the object. If a component of that type already exists, it returns the existing one.
    *   `Draw()`: `virtual void` - Renders the object.
    *   `GetComponent()`: `template<typename T> T*` - Retrieves a component of type `T` attached to the object, or `nullptr` if not found.
    *   `OpenEditor()`: `virtual void` - Opens an editor window for the object (e.g., using ImGui).
    *   `RemoveComponent()`: `template<typename T> void` - Removes a component of type `T` from the object.
    *   `RenderEditorWindow()`: `virtual void` - Renders the object's editor window content.
    *   `Update()`: `virtual void` - Updates the object's state.
    *   `~Object()`: Virtual destructor for proper cleanup of derived objects.

## Pendulum

*   **Description**: Represents a pendulum object in the simulation, composed of a rod (rectangle) and a bob (circle).
*   **Properties**:
    *   (Inherits properties from `Object`)
    *   `shape`: `Shape*` - Pointer to the `Shape` component representing the pendulum rod.
    *   `shape2`: `Shape*` - Pointer to the `Shape` component representing the pendulum bob.
*   **Methods**:
    *   `Draw()`: `void` - Draws both the pendulum rod and bob on the application window.
    *   `Pendulum(const float length, const float radius, const float weight, const float x, const float y, const std::string& name)`: Constructor to create a pendulum with specified length, radius, weight, position, and name.
    *   `RenderEditorWindow()`: `void` - Renders the editor window for the pendulum.
    *   `Update()`: `void` - Updates the visual properties and position of the pendulum's rod and bob based on its transform and physics.

## Rectangle

*   **Description**: Represents a rectangular shape in the simulation, inheriting from `Object` and `Shape`.
*   **Properties**:
    *   (Inherits properties from `Object` and `Shape`)
*   **Methods**:
    *   `Rectangle(const float width, const float height, const float x, const float y, const std::string& name)`: Constructor to create a rectangle with specified dimensions, position, and name.
    *   `Draw()`: `void` - Draws the rectangle on the application window.
    *   `RenderEditorWindow()`: `void` - Renders the editor window for the rectangle.
    *   `Update()`: `void` - Updates the rectangle's visual properties based on its transform.

## RigidBody

*   **Description**: A component that adds physics properties and behavior (mass, velocity, acceleration, elasticity) to an `Object`.
*   **Properties**:
    *   `acceleration`: `Acceleration` - The acceleration applied to the rigid body.
    *   `elasticity`: `float` - The elasticity coefficient for collisions.
    *   `mass`: `float` - The mass of the rigid body.
    *   `stationary`: `bool` - Indicates if the rigid body is stationary (not affected by physics).
    *   `velocity`: `Vector2` - The current velocity of the rigid body.
*   **Methods**:
    *   `RigidBody()`: Default constructor.
    *   `RigidBody(Object* entity)`: Constructor that initializes the rigid body with its owning entity.
    *   `RigidBody(Vector2 velocity, Acceleration acceleration, float mass)`: Constructor to create a rigid body with specified initial velocity, acceleration, and mass.
    *   `RenderEditor()`: `void` - Renders editor UI for the rigid body.
    *   `SetMass(float mass)`: Sets the mass of the rigid body.
    *   `Update(float deltaTime)`: Updates the rigid body's velocity and position based on acceleration and delta time.

## Scene

*   **Description**: Base class for all simulation scenes, providing an interface for scene initialization, execution, and object management.
*   **Properties**:
    *   `objectsList`: `std::list<Object*>` - A list of all objects present in the scene.
    *   `running`: `bool*` - Pointer to a boolean indicating if the application is running.
    *   `view`: `sf::View*` - Pointer to the SFML view used for rendering the scene.
*   **Methods**:
    *   `CollisionDetector(float deltaTime)`: `virtual void` - Detects and resolves collisions between objects in the scene.
    *   `InitializeObjects()`: `virtual void` - Initializes the objects specific to this scene.
    *   `PhysicsHandler()`: `virtual void` - Handles the physics updates for the scene.
    *   `Run()`: `virtual void` - Executes the main loop for the scene, including updates and rendering.
    *   `Unload()`: `virtual void` - Unloads scene-specific resources.
    *   `~Scene()`: Virtual destructor for proper cleanup of derived scenes.

## Shape

*   **Description**: Base class for all drawable shapes in the simulation, providing common properties like color and visibility, and integration with SFML shapes.
*   **Properties**:
    *   `color`: `Color` - The color of the shape.
    *   `geometry`: `Vector2` - Represents the dimensions or radius of the shape.
    *   `shape`: `sf::Shape*` - Pointer to the underlying SFML shape object.
    *   `shape2`: `sf::Shape*` - Pointer to a second SFML shape object, used for dual shapes.
    *   `visible`: `bool` - Indicates whether the shape is currently visible.
    *   `xGeometry`: `std::string` - String description for the x-dimension of the shape's geometry.
    *   `yGeometry`: `std::string` - String description for the y-dimension of the shape's geometry.
*   **Methods**:
    *   `Get()`: `sf::Shape*` - Returns a pointer to the primary SFML shape object.
    *   `Get2()`: `virtual sf::Shape*` - Returns a pointer to the secondary SFML shape object (for dual shapes).
    *   `RenderEditor()`: `void` - Renders editor UI for the shape.
    *   `Shape()`: Default constructor.
    *   `Shape(Object* entity)`: Constructor that initializes the shape with its owning entity.
    *   `Shape(sf::Shape* shape, Object* entity)`: Constructor that initializes the shape with an SFML shape and its owning entity.
    *   `Shape(sf::Shape* shape, const std::string& xGeometry, const std::string& yGeometry, const Vector2* geometry, Object* entity)`: Constructor that initializes the shape with an SFML shape, geometry descriptions, and its owning entity.
    *   `Visible()`: `bool` - Returns true if the shape is visible, false otherwise.

## Transform

*   **Description**: A component that defines the position, scale, rotation, and size of an `Object` in 2D space.
*   **Properties**:
    *   `position`: `Vector2` - The 2D position of the object.
    *   `rotation`: `float` - The rotation angle of the object in degrees.
    *   `scale`: `Vector2` - The 2D scale of the object.
    *   `size`: `Vector2` - The base dimensions of the object.
*   **Methods**:
    *   `getDimensions()`: `Vector2` - Calculates and returns the effective dimensions of the object (size * scale).
    *   `operator sf::Transform() const`: `sf::Transform` - Conversion operator to SFML's `sf::Transform` for rendering.
    *   `RenderEditor()`: `void` - Renders editor UI for the transform component.
    *   `Transform()`: Default constructor.
    *   `Transform(float x, float y, float rotation, Object* entity)`: Constructor to create a transform with specified position, rotation, and owning entity.
    *   `Transform(Object* entity)`: Constructor that initializes the transform with its owning entity.
    *   `~Transform()`: Destructor.

## Vector2

*   **Description**: A utility class for 2D vector operations, including arithmetic, magnitude, normalization, and conversions to/from SFML's `sf::Vector2f`.
*   **Properties**:
    *   `x`: `float*` - Pointer to the x-component of the vector.
    *   `y`: `float*` - Pointer to the y-component of the vector.
    *   `arr`: `float[2]` - Private array storing the x and y components of the vector.
*   **Methods**:
    *   `Array()`: `float*` - Returns a pointer to the internal float array representing the x and y components.
    *   `Distance(const Vector2& a, const Vector2& b)`: `static float` - Calculates the Euclidean distance between two Vector2 objects.
    *   `Dot(const Vector2& other)`: `float` - Calculates the dot product with another Vector2.
    *   `FromV2F(sf::Vector2f vector)`: `static Vector2` - Converts an SFML `sf::Vector2f` to a Vector2 object.
    *   `Magnitude()`: `float` - Calculates the magnitude (length) of the vector.
    *   `Normalized()`: `Vector2` - Returns a new Vector2 with the same direction but a magnitude of 1.
    *   `operator*(const Vector2& other)`: `Vector2` - Performs element-wise multiplication with another Vector2.
    *   `operator*(float scalar)`: `Vector2` - Multiplies the vector by a scalar.
    *   `operator+(const Vector2& other)`: `Vector2` - Adds another Vector2 to this vector.
    *   `operator-(const Vector2& other)`: `Vector2` - Subtracts another Vector2 from this vector.
    *   `operator/(float scalar)`: `Vector2` - Divides the vector by a scalar.
    *   `operator=(const Vector2& other)`: `Vector2&` - Assignment operator.
    *   `ToV2F()`: `sf::Vector2f` - Converts the Vector2 object to an SFML `sf::Vector2f`.
    *   `Vector2()`: Default constructor.
    *   `Vector2(float x, float y)`: Constructor to create a vector with specified x and y components.
    *   `Vector2(const Vector2& other)`: Copy constructor.
    *   `Vector2(sf::Vector2f vector)`: Constructor to create a vector from an an SFML `sf::Vector2f`.

## Pendulum

*   **Description**: Represents a pendulum object in the simulation, composed of a rod (rectangle) and a bob (circle).
*   **Properties**:
    *   (Inherits properties from `Object`)
    *   `shape`: `Shape*` - Pointer to the `Shape` component representing the pendulum rod.
    *   `shape2`: `Shape*` - Pointer to the `Shape` component representing the pendulum bob.
*   **Methods**:
    *   `Draw()`: `void` - Draws both the pendulum rod and bob on the application window.
    *   `Pendulum(const float length, const float radius, const float weight, const float x, const float y, const std::string& name)`: Constructor to create a pendulum with specified length, radius, weight, position, and name.
    *   `RenderEditorWindow()`: `void` - Renders the editor window for the pendulum.
    *   `Update()`: `void` - Updates the visual properties and position of the pendulum's rod and bob based on its transform and physics.
