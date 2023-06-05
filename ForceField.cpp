#include "Physics.h"
#include "imgui.h"
#include "Object.h"
#include <iostream>

const double G = 6.6743e-3;

void ForceField::Update(std::list<Object*>* objectsList, float deltaTime) {
	if (!body) {
		return;
	}
	for (Object* object : *objectsList) {
		RigidBody* rigidBody = object->GetComponent<RigidBody>();
		if (object == this->entity) {
			continue;
		}
		if (rigidBody) {
			if (rigidBody->stationary) {
				continue;
			}
			Vector2 direction = (entity->transform->position - object->transform->position).Normalized();
			float distance = Vector2::Distance(entity->transform->position, object->transform->position) / 1000.f;
			float force = G * (body->mass) / (distance * distance);
			force *= magnitude;
			*rigidBody->velocity.x += *direction.x * force * deltaTime;
			*rigidBody->velocity.y += *direction.y * force * deltaTime;
		}
	}
}

ForceField::ForceField(Object* entity) {
	this->entity = entity;

}

void ForceField::RenderEditor() {
	ImGui::Text("ForceField");
	ImGui::DragFloat("Power", &magnitude, 0.02f, 0.f, FLT_MAX);
	ImGui::Spacing();

}