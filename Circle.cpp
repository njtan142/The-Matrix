#include "shapes.h"
#include "Physics.h"
#include "Transform.h"
#include "imgui.h"
#include <string>
#include "Component.h"
#include "Application.h"


Circle::Circle(const float width, const float height, const float x, const float y, const std::string& name) {
	this->AddComponent<Transform>(std::make_unique<Transform>(x, y, 0, this));
	transform = this->GetComponent<Transform>();
	transform->size = Vector2(width, height);


	this->AddComponent(
		std::make_unique<Shape>(std::make_unique<sf::CircleShape>(width, height),
			"Width",
			"Height",
			std::make_unique<Vector2>(width, height),
			this)
	);
	

	this->name = name;
	edit = false;
}

void Circle::RenderEditorWindow() {
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

void Circle::Update() {
    Shape* circleShapeComponent = this->GetComponent<Shape>();
    if (!circleShapeComponent) {
        // Handle error: Shape component not found
        return;
    }

    sf::Shape* sfShape = circleShapeComponent->Get();
    if (!sfShape) {
        // Handle error: sf::Shape object not found
        return;
    }

    sfShape->setPosition(*transform->position.x, *transform->position.y);
    sfShape->setRotation(transform->rotation);

    if (sf::CircleShape* rectShape = dynamic_cast<sf::CircleShape*>(sfShape)) {
        rectShape->setRadius(
            *circleShapeComponent->geometry.x * *transform->scale.x
        );
    }

    sfShape->setFillColor(circleShapeComponent->color.toSFC());
}


void Circle::Draw(sf::RenderWindow& window) { // Modified signature
    Shape* circleShapeComponent = this->GetComponent<Shape>();
    if (!circleShapeComponent) {
        // Handle error: Shape component not found
        return;
    }

    sf::Shape* sfShape = circleShapeComponent->Get();
    if (!sfShape) {
        // Handle error: sf::Shape object not found
        return;
    }
	window.draw(*sfShape); // Use passed window
}