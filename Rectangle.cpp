#include "shapes.h"
#include "Physics.h"
#include "Transform.h"
#include "imgui.h"
#include <string>
#include "Component.h"
#include "Application.h"


Rectangle::Rectangle(const float width, const float height, const float x, const float y, const std::string &name) {
	this->AddComponent<Transform>(new Transform(x, y, 0, this));
	transform = this->GetComponent<Transform>();
	transform->size = Vector2(width, height);


	this->AddComponent(
		new Shape(new sf::RectangleShape((new Vector2(width, height))->ToV2F()),
			"Width",
			"Height",
			new Vector2(width, height),
			this)
	);
	shape = this->GetComponent<Shape>();

	this->name = name;
	edit = false;
}

void Rectangle::RenderEditorWindow() {
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

void Rectangle::Update() {
	shape->Get()->setPosition(*transform->position.x, *transform->position.y);
	shape->Get()->setRotation(transform->rotation);

	if (sf::RectangleShape* rectShape = dynamic_cast<sf::RectangleShape*>(shape->Get())) { // cast shape pointer to sf::RectangleShape
		rectShape->setSize(
			(shape->geometry * transform->scale).ToV2F()
		);
		rectShape->setOrigin(
			rectShape->getSize().x / 2.f,
			rectShape->getSize().y / 2.f
		);
	}

	shape->Get()->setFillColor(shape->color.toSFC());
}

void Rectangle::Draw() {
	Application::window.draw(*shape->Get());
}


