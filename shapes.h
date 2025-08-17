#pragma once
#include "Object.h"
#include "Shape.h"
#include "SFML/Graphics.hpp" // Include SFML/Graphics.hpp for sf::RenderWindow
#include <memory> // Added for std::unique_ptr

class Rectangle : public Object {
public:
	Rectangle(const float width, const float height, const float x, const float y, const std::string &name);

	void RenderEditorWindow() override;

	void Update() override;

	void Draw(sf::RenderWindow& window) override; // Modified signature

public:
	
};

class Circle : public Object {
public:
	Circle(const float width, const float height, const float x, const float y, const std::string& name);

	void RenderEditorWindow() override;

	void Update() override;

	void Draw(sf::RenderWindow& window) override; // Modified signature

public:
	
};

class Pendulum : public Object {
public: 
	Pendulum(const float length, const float radius, const float weight, const float x, const float y, const std::string& name);

	void RenderEditorWindow() override;

	void Update() override;

	void Draw(sf::RenderWindow& window) override; // Modified signature

	~Pendulum() {
		delete shape2;
	}

public:
	Shape* shape;
	Shape* shape2;
};