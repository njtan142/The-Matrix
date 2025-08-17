#include "Object.h"
#include "Component.h"
#include <vector>
#include "Shape.h"
#include "Transform.h"

void Object::OpenEditor() {
	edit = true;
}

void Object::Draw(sf::RenderWindow& window) {
    // Default empty implementation for the base class
    // Derived classes will provide their specific drawing logic
}