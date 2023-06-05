#include "EnergyConservationBilliard.h"
#include "Application.h"
#include "shapes.h"
#include "Physics.h"

EnergyConservationSceneBilliard::EnergyConservationSceneBilliard(sf::View* view) {
	running = &Application::running;
	this->view = view;
}

void EnergyConservationSceneBilliard::InitializeObjects() {
	Circle* rectangle = new Circle(25, 100, 100, 100, "obj1");
	rectangle->AddComponent<RigidBody>();
	RigidBody* rb = rectangle->GetComponent<RigidBody>();
	*rb->velocity.x = -500;
	*rb->velocity.y = 2000;
	rb->mass = 1;
	objectsList.push_back(rectangle);

	Circle* rectangle1 = new Circle(25, 100, 400, 750, "obj2");
	rectangle1->AddComponent<RigidBody>()->mass = 1;
	objectsList.push_back(rectangle1);

	for (int i = 0; i < 15; i++) {
		Circle* rectangle1 = new Circle(25, 100, -500 + (i * 110), 750, "obj" + i);
		rectangle1->AddComponent<RigidBody>()->elasticity = 0.5;
		objectsList.push_back(rectangle1);
	}

	Rectangle* wall1 = new Rectangle(5, 2000, -600, 400, "left");
	wall1->AddComponent<RigidBody>()->stationary = true;
	objectsList.push_back(wall1);

	Rectangle* wall2 = new Rectangle(5, 2000, 1500, 400, "right");
	wall2->AddComponent<RigidBody>()->stationary = true;
	objectsList.push_back(wall2);

	Rectangle* wall3 = new Rectangle(2100, 5, 450, -300, "up");
	wall3->AddComponent<RigidBody>()->stationary = true;
	objectsList.push_back(wall3);

	Rectangle* wall4 = new Rectangle(2100, 5, 450, 1200, "down");
	wall4->AddComponent<RigidBody>()->stationary = true;
	objectsList.push_back(wall4);

}