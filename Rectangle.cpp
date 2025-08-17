#include "shapes.h"
#include "Physics.h"
#include "Transform.h"
#include "imgui.h"
#include <string>
#include "Component.h"
#include "Application.h"


Rectangle::Rectangle(const float width, const float height, const float x, const float y, const std::string& name) {
	this->AddComponent<Transform>(std::make_unique<Transform>(x, y, 0, this));
	transform = this->GetComponent<Transform>();
	transform->size = Vector2(width, height);


	this->AddComponent(
		std::make_unique<Shape>(std::make_unique<sf::RectangleShape>((new Vector2(width, height))->ToV2F()),
			"Width",
			"Height",
			std::make_unique<Vector2>(width, height),
			this)
	);
	

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

	for (std::vector<std::unique_ptr<Component>>::iterator it = components.begin(); it != components.end(); ++it) {
		(*it)->RenderEditor();
		ImGui::Dummy(ImVec2(0.0f, 10.0f));  // adds a 10-pixel tall blank widget
	}


	if (ImGui::Button("Close"))
	{
		edit = false;
	}

	ImGui::End();
}

void Rectangle::Update() {
	this->GetComponent<Shape>()->Get()->setPosition(*transform->position.x, *transform->position.y);
	this->GetComponent<Shape>()->Get()->setRotation(transform->rotation);

	if (sf::RectangleShape* rectShape = dynamic_cast<sf::RectangleShape*>(this->GetComponent<Shape>()->Get())) { // cast shape pointer to sf::RectangleShape
		rectShape->setSize(
			sf::Vector2f(
				*this->GetComponent<Shape>()->geometry.x * *transform->scale.x,
				*this->GetComponent<Shape>()->geometry.y * *transform->scale.y
			)
		);
	}

	this->GetComponent<Shape>()->Get()->setFillColor(this->GetComponent<Shape>()->color.toSFC());
}


void Rectangle::Draw(sf::RenderWindow& window) { // Modified signature
	window.draw(*this->GetComponent<Shape>()->Get()); // Use passed window
}