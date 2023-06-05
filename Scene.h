#pragma once
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"

#include <chrono>
#include <thread>
#include <list>

#include "Object.h"

class Scene {
public:
	virtual ~Scene() {}
	Scene() {}

	virtual void InitializeObjects() {};
	virtual void Run();
	virtual void Unload() {};


public:
	std::list<Object*> objectsList;
	bool* running = nullptr;
	sf::View* view = nullptr;

private:
	virtual void PhysicsHandler();
	virtual void CollisionDetector(float deltaTime);
};
