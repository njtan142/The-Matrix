#include "AccellerationScene.h"
#include "Application.h"
#include "shapes.h"
#include "Physics.h"

AccellerationScene::AccellerationScene(sf::View* view) {
	running = &Application::running;
	this->view = view;
}

void AccellerationScene::InitializeObjects() {
	Rectangle* rectangle = new Rectangle(100, 100, 400, 750, "obj1");
	rectangle->AddComponent<RigidBody>();
	RigidBody* rb = rectangle->GetComponent<RigidBody>();
	objectsList.push_back(rectangle);
	rectangle->OpenEditor();


	view->setSize(view->getSize() * (5.f));
}