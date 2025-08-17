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

Scene::Scene(Application& app) : app(app) {} // Constructor implementation

Scene::~Scene() {
    for (Object* obj : objectsList) {
        delete obj;
    }
    objectsList.clear();
}

void Scene::UpdateAndRender(float deltaTime) {
    // This function now performs one frame's worth of physics and rendering
    // The main loop is now in Application::Run()

    app.getWindow().clear(sf::Color(18, 33, 43)); // Color background

    for (Object* object : objectsList) {
        Shape& objectShape = *object->GetComponent<Shape>();
        object->RenderEditorWindow();
        object->Update();
        if (objectShape.Visible()) {
            object->Draw(app.getWindow()); // Pass app.getWindow() here
        }
    }

    // Call PhysicsHandler directly on the main thread
    PhysicsHandler(deltaTime);
}


void Scene::PhysicsHandler(float deltaTime) {
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
                normal = Vector2(
                    (*normal.x + -*velocityDirection.x) / 2,
                    (*normal.y + -*velocityDirection.y) / 2
                ).Normalized();
            }


            Vector2 tangent(*normal.y, -*normal.x);
            float velAlongNormal = (b->velocity - a->velocity).Dot(normal);


            if (velAlongNormal > 0) {
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
            continue;
        }
        Shape* a_objectShape = a_object->GetComponent<Shape>();
        if (!a_objectShape) {
            continue;
        }
        sf::Shape* a_objectSFShape = a_objectShape->Get();
        if (!a_objectSFShape) {
            continue;
        }
        sf::FloatRect a_objectBounds = a_objectSFShape->getGlobalBounds();
        a_object->Update();
        for (Object* b_object : objectsList) {
            if (!b_object) {
                continue;
            }
            if (a_object == b_object) {
                continue;
            }
            b_object->Update();

            Shape* b_objectShape = b_object->GetComponent<Shape>();
            if (!b_objectShape) {
                continue;
            }
            sf::Shape* b_objectSFShape = b_objectShape->Get();
            if (!b_objectSFShape) {
                continue;
            }

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
