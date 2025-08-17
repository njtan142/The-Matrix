#include "shapes.h"
#include "imgui.h"
#include <string>
#include "Application.h"
#include <cmath>
#define M_PI 3.14159265358979323846


Pendulum::Pendulum(const float length, const float radius, const float weight, const float x, const float y, const std::string& name) {
	this->AddComponent<Transform>(new Transform(x, y, 0, this));
	transform = this->GetComponent<Transform>();
	transform->size = Vector2(length, radius);

	Vector2 circleCoord(x, y + length);

	this->AddComponent<Shape>(
		new Shape(
			new sf::RectangleShape(Vector2(5, length).ToV2F()),
			"Length",
			"Height",
			new Vector2(5, length),
			this
		)
		/*new Shape(
			new sf::CircleShape(radius, 25),
			"Radius",
			"Sides",
			new Vector2(radius, 25),
			this
		)*/
		/*new DualShape(
			new sf::RectangleShape(Vector2(5, length).ToV2F()),
			new sf::CircleShape(radius, 25),
			"Length",
			"Height",
			"x",
			"y",
			new Vector2(5, length),
			new Vector2(radius, 25),
			this
		)*/
	);

	shape = this->GetComponent<Shape>();
	shape2 = new Shape(
		new sf::CircleShape(radius, 25),
		"Radius",
		"Sides",
		new Vector2(radius, 25),
		this
	);

	this->name = name;
	edit = true;
}

void Pendulum::RenderEditorWindow() {
	if (!edit) {
		return;
	}
	std::string windowName = name + "Editor Window";
	ImGui::Begin(windowName.c_str());
	ImGui::Spacing();

	for (Component* component : components) {
		component->RenderEditor();
		ImGui::Dummy(ImVec2(0.0f, 10.0f));  // adds a 10-pixel tall blank widget
	}


	if (ImGui::Button("Close"))
	{
		edit = false;
	}

	ImGui::End();
}

void Pendulum::Update() {
	
	float length = 0.f;
	float angle = 0.f;
	float x = 0.f;
	float y = 0.f;

	if (sf::RectangleShape* rectShape = dynamic_cast<sf::RectangleShape*>(shape->Get())) { // cast shape pointer to sf::RectangleShape
		
		rectShape->setOrigin(
			rectShape->getSize().x / 2.f,
			0
		);

		length = rectShape->getSize().y;
		angle = (rectShape->getRotation() + 90) * M_PI / 180.0;
		x = length * cos(angle);
		y = length * sin(angle);

	}

	if (sf::CircleShape* circleShape = dynamic_cast<sf::CircleShape*>(shape2->Get())) { // cast shape pointer to sf::RectangleShape
		float radius = circleShape->getRadius();
		circleShape->setOrigin(
			radius, radius
		);
	}

	shape->Get()->setPosition(*transform->position.x, *transform->position.y);
	shape->Get()->setRotation(transform->rotation);
	shape2->Get()->setPosition(*transform->position.x + x, *transform->position.y + y);


	shape->Get()->setFillColor(shape->color.toSFC());
	shape2->Get()->setFillColor(shape->color.toSFC());

}

void Pendulum::Draw(sf::RenderWindow& window) { // Modified signature
	window.draw(*shape->Get());
	window.draw(*shape2->Get());

}

// TODO: do the method call draw for all objects