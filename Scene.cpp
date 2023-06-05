#include "Scene.h"
#include "Application.h"
#include "Physics.h"
#include "Shape.h"
#include "Object.h"
#include "Component.h"
#include <future>
#include <cmath>
#include <iostream>

#ifndef NDEBUG
#include <iostream>
#define DEBUG_LOG(msg) std::cout << msg << std::endl
#else
#define DEBUG_LOG(msg) ((void)0)
#endif

void Scene::Run() {
	sf::Clock deltaClock;

	for (Object* object : objectsList) {
		Shape& objectShape = *object->GetComponent<Shape>();
		object->Update();
	}

	Application::previousMousePos = sf::Mouse::getPosition(Application::window);
	std::thread physicsThread([&]() { PhysicsHandler(); });
	while (Application::window.isOpen() && Application::running)
	{
		Application::ListenEvent(view, &objectsList);
		Application::previousMousePos = sf::Mouse::getPosition(Application::window);

		ImGui::SFML::Update(Application::window, deltaClock.restart());

		Application::window.clear(sf::Color(18, 33, 43)); // Color background

		for (Object* object : objectsList) {
			Shape& objectShape = *object->GetComponent<Shape>();
			object->RenderEditorWindow();
			object->Update();
			if (objectShape.Visible()) {
				object->Draw();
			}
		}
		if (Application::window.isOpen() && Application::running) {
			Application::RenderGameControls(*view);
			ImGui::SFML::Render(Application::window);
		}
		else {
			Application::running = false;
			continue;
		}
		Application::window.display();
	}
	std::cout << "Closing" << std::endl;
	Application::running = false;
	physicsThread.join();
	objectsList.clear();
	std::cout << "Closed" << std::endl;

}


void Scene::PhysicsHandler() {
	const int FPS = 120;
	const std::chrono::milliseconds FRAME_TIME_MS(1000 / FPS);
	std::chrono::steady_clock::time_point prevFrameTime = std::chrono::high_resolution_clock::now();

	while (Application::running) {
		std::chrono::steady_clock::time_point currFrameTime = std::chrono::high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float, std::chrono::milliseconds::period>(currFrameTime - prevFrameTime).count() / 1000.0f;
		prevFrameTime = currFrameTime;

		for (Object* object : objectsList) {
			ForceField* forceField = object->GetComponent<ForceField>();
			if (forceField) {
				forceField->Update(&objectsList, deltaTime);
			}
			RigidBody* rigidBody = object->GetComponent<RigidBody>();
			if (rigidBody) {
				rigidBody->Update(deltaTime);
			}
		}
		CollisionDetector(deltaTime);
	}
}

namespace Dynamics {
	namespace Vector {
		sf::Vector2f GetNormal(Transform a, Transform b);
	}
	namespace Momentum {
		void Conserve(RigidBody* a, RigidBody* b, float deltaTime) {
			if (!(a && b)) {
				return;
			}
			if (a->stationary && b->stationary) {
				return;
			}
			DEBUG_LOG("Collission Detected: " << a->entity->name << " | " << b->entity->name);


			Vector2 normal = b->entity->transform->position - a->entity->transform->position;
			normal = normal.Normalized();
			if (a->stationary || b->stationary) {
				Vector2 velocityDirection;
				if (a->stationary) {
					velocityDirection = b->velocity.Normalized();
				}
				else {
					velocityDirection = a->velocity.Normalized();
				}
				DEBUG_LOG(*normal.x << " || " << *normal.y);
				DEBUG_LOG(*velocityDirection.x << " || " << *velocityDirection.y);
				normal = Vector2(
					(*normal.x + -*velocityDirection.x) / 2,
					(*normal.y + -*velocityDirection.y) / 2
				).Normalized();
				DEBUG_LOG(*normal.x << " || " << *normal.y);
			}


			Vector2 tangent(*normal.y, -*normal.x);
			float velAlongNormal = (b->velocity - a->velocity).Dot(normal);


			if (velAlongNormal > 0) {
				DEBUG_LOG("moving away");
				return;
			}

			float restitution = a->elasticity + b->elasticity;

			if (b->stationary) {
				Vector2 bounceNormal = normal * a->velocity;
				Vector2 direction(0, 0);
				if (b->entity->name == "left" || b->entity->name == "right") {
					direction = Vector2(-1, 1);
				}
				else {
					direction = Vector2(1, -1);
				}
				a->velocity = Vector2(*a->velocity.x * *direction.x, *a->velocity.y * *direction.y) * restitution;
				a->Update(deltaTime);
				return;
			}
			if (a->stationary) {
				Vector2 direction(0, 0);
				if (a->entity->name == "left" || a->entity->name == "right") {
					direction = Vector2(-1, 1);
				}
				else {
					direction = Vector2(1, -1);
				}
				b->velocity = Vector2(*b->velocity.x * *direction.x, *b->velocity.y * *direction.y) * restitution;
				b->Update(deltaTime);
				return;
			}
			normal = b->entity->transform->position - a->entity->transform->position;
			normal = normal.Normalized();
			velAlongNormal = (b->velocity - a->velocity).Dot(normal);
			float impulse = -(1 + restitution) * velAlongNormal / (a->mass + b->mass);
			a->velocity = a->velocity - normal * impulse * b->mass;
			b->velocity = b->velocity + normal * impulse * a->mass;


			DEBUG_LOG("A velocity: " << *a->velocity.x << " , " << *a->velocity.y);
			DEBUG_LOG("B velocity: " << *b->velocity.x << " , " << *b->velocity.y);

			a->Update(deltaTime);
			b->Update(deltaTime);
		}
	}

	namespace Vector {
		sf::Vector2f GetNormal(Transform a, Transform b) {
			sf::Transform a_Transform = static_cast<sf::Transform>(a);
			sf::Transform b_Transform = static_cast<sf::Transform>(b);

			// get the position vectors of the transforms
			sf::Vector2f pos1 = a_Transform.transformPoint(0, 0);
			sf::Vector2f pos2 = b_Transform.transformPoint(0, 0);
			sf::Vector2f direction = pos2 - pos1;
			sf::Vector2f normal(-direction.y, direction.x);

			//std::cout << "normal: " << normal.x << ", " << normal.y << std::endl;
			return normal;
		}


	}
}

void Scene::CollisionDetector(float deltaTime) {
	std::list<Object*>* obslst = &objectsList;

	for (Object* a_object : objectsList) {
		if (!a_object) {
			return;
		}
		sf::Shape* a_objectSFShape = a_object->GetComponent<Shape>()->Get();
		sf::FloatRect a_objectBounds = a_objectSFShape->getGlobalBounds();
		a_object->Update();
		for (Object* b_object : objectsList) {
			if (!b_object) {
				return;
			}
			if (a_object == b_object) {
				continue;
			}
			b_object->Update();

			sf::Shape* b_objectSFShape = b_object->GetComponent<Shape>()->Get();

			bool intersection = b_objectSFShape->getGlobalBounds().intersects(a_objectBounds);

			if (intersection) {

				Dynamics::Momentum::Conserve(
					a_object->GetComponent<RigidBody>(),
					b_object->GetComponent<RigidBody>(),
					deltaTime
				);
			}
		}
	}
}



