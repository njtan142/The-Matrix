#include "Physics.h"
#include "imgui.h"
#include "Object.h"


void RigidBody::Update(float deltaTime) {
	*velocity.x += *acceleration.direction.x * acceleration.magnitude * deltaTime;
	*velocity.y += *acceleration.direction.y * acceleration.magnitude * deltaTime;

	Vector2* position = &entity->transform->position;
	*position->x += *velocity.x * deltaTime;
	*position->y += *velocity.y * deltaTime;
}

void RigidBody::SetMass(float mass) {
	this->mass = mass;
}

RigidBody::RigidBody(Vector2 velocity, Acceleration acceleration, float mass) : velocity(velocity), acceleration(acceleration), mass(mass) {}

RigidBody::RigidBody() : velocity(0, 0), acceleration() {}

RigidBody::RigidBody(Object* entity) {
	this->entity = entity;
}

void RigidBody::RenderEditor() {
	ImGui::Text("RigidBody");
	ImGui::Separator();
	ImGui::DragFloat2("Velocity", velocity.Array());
	ImGui::DragFloat("Mass", &mass, 0.02f, 0.f, FLT_MAX);
	ImGui::Spacing();
	ImGui::DragFloat2("Direction", acceleration.direction.Array(), 0.02f, -1.f, 1.f);
	ImGui::DragFloat("Magnitude", &acceleration.magnitude, 0.02f, 0.f, FLT_MAX);
	ImGui::DragFloat("Restitution", &elasticity, 0.002f, 0.f, 0.6f);
	ImGui::Spacing();

}

