#pragma once
#include "Component.h"
#include "Vector2.h"
#include "SFML/Graphics.hpp"

class Transform : public Component {
public:
	Vector2 position;
	Vector2 scale;
	float rotation;
	Vector2 size;

	~Transform() {
		entity = nullptr;
	};
	Transform();
	Transform(float x, float y, float rotation, Object* entity);
	Transform(Object* entity);

	Vector2 getDimensions() {
		return size * scale;
	}

	void RenderEditor() override;

	operator sf::Transform() const {
		// Create an identity transform
		sf::Transform transform;

		// Apply translation
		transform.translate(*position.x, *position.y);

		// Apply rotation
		transform.rotate(rotation);

		// Apply scaling
		transform.scale(*scale.x, *scale.y);

		return transform;
	}
};
