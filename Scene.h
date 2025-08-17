#pragma once
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include <chrono>
#include <thread>
#include <list>

#include "Object.h"
class Application; // Forward declaration

#include "Application.h" // Keep this include for full definition

class Scene {
public:
    virtual ~Scene();
    Scene(Application& app); // Modified constructor to accept Application reference

    virtual void InitializeObjects() {};
    virtual void UpdateAndRender(float deltaTime); // Renamed from Run()
    virtual void Unload() {};


public:
    std::list<Object*> objectsList;
    sf::View* view = nullptr; // Keep view for now

private:
    Application& app; // Reference to the Application instance
    virtual void PhysicsHandler(float deltaTime);
    virtual void CollisionDetector(float deltaTime);
};
