#include "BounceSimulationScene.h"
#include "Application.h"
#include "shapes.h"
#include "Physics.h"

BounceSimulationScene::BounceSimulationScene(sf::View* view, Application& app) : Scene(app) { // Pass app to base constructor
    this->view = view;
}

void BounceSimulationScene::InitializeObjects() {
    Rectangle* rectangle = new Rectangle(100, 100, 450, 0, "obj1");
    rectangle->AddComponent<RigidBody>();
    RigidBody* rb = rectangle->GetComponent<RigidBody>();
    *rb->acceleration.direction.y = 1;
    rb->acceleration.magnitude = 5000;
    rectangle->OpenEditor();
    objectsList.push_back(rectangle);

    Rectangle* wall1 = new Rectangle(5, 2000, -600, 400, "left");
    wall1->AddComponent<RigidBody>()->stationary = true;
    objectsList.push_back(wall1);

    Rectangle* wall2 = new Rectangle(5, 2000, 1500, 400, "right");
    wall2->AddComponent<RigidBody>()->stationary = true;
    objectsList.push_back(wall2);

    Rectangle* wall3 = new Rectangle(2100, 5, 450, -4000, "up");
    wall3->AddComponent<RigidBody>()->stationary = true;
    //objectsList.push_back(wall3);

    Rectangle* wall4 = new Rectangle(2100, 5, 450, 800, "down");
    wall4->AddComponent<RigidBody>()->stationary = true;
    objectsList.push_back(wall4);

}