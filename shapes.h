#pragma once
#include "Object.h"
#include "Shape.h"

class Rectangle : public Object {
public:
	Rectangle(const float width, const float height, const float x, const float y, const std::string &name);

	void RenderEditorWindow() override;

	void Update() override;

	void Draw() override;

	~Rectangle() {
		if (shape != nullptr) {
			delete shape;
			shape = nullptr;
		}
	}

public:
	Shape* shape;
};

class Circle : public Object {
public:
	Circle(const float width, const float height, const float x, const float y, const std::string& name);

	void RenderEditorWindow() override;

	void Update() override;

	void Draw() override;

	~Circle() {
		if (shape != nullptr) {
			delete shape;
			shape = nullptr;
		}
	}

public:
	Shape* shape;
};

class Pendulum : public Object {
public: 
	Pendulum(const float length, const float radius, const float weight, const float x, const float y, const std::string& name);

	void RenderEditorWindow() override;

	void Update() override;

	void Draw() override;

public:
	Shape* shape;
	Shape* shape2;
};


