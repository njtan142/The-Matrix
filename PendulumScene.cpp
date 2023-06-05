#include "PendulumScene.h"
#include "Application.h"
#include "shapes.h"
#include "Physics.h"

PendulumScene::PendulumScene(sf::View* view) {
	running = &Application::running;
	this->view = view;
}

void PendulumScene::InitializeObjects() {
	Rectangle* rectangle = new Rectangle(100, 100, 400, 750, "obj1");
	rectangle->AddComponent<RigidBody>();
	RigidBody* rb = rectangle->GetComponent<RigidBody>();
	//objectsList.push_back(rectangle);

	Pendulum* pendulum = new Pendulum(600, 50, 1, 200, 200, "pendulum1");
	pendulum->AddComponent<RigidBody>();
	RigidBody* pendulumRB = pendulum->GetComponent<RigidBody>();
	objectsList.push_back(pendulum);
}