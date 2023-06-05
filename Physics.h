#pragma once
#include "Vector2.h"
#include "Component.h"
#include <list>


class Acceleration {
public:
	Acceleration();
	Acceleration(float dx, float dy, float magnitude);

public:
	Vector2 direction;
	float magnitude;
};


class RigidBody : public Component {
public:
	Vector2 velocity;
	Acceleration acceleration;
	float mass = 1.f;
	float elasticity = 0.5f;
	bool stationary = false;

	void Update(float deltaTime);

	void SetMass(float mass);

	RigidBody(Vector2 velocity, Acceleration acceleration, float mass);

	RigidBody();

	RigidBody(Object* entity);

	void RenderEditor() override;
};

class ForceField : public Component {
public:
	float radius = 1.0f;
	float magnitude = 1.0f;
	Vector2 net_force = Vector2(0, 0);
	RigidBody* body = nullptr;	

	ForceField() {}
	ForceField(Object* entity);
	void RenderEditor() override;
	void Update(std::list<Object*>* objectsList, float deltaTime);

};


