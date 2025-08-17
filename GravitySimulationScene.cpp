#include "GravitySimulationScene.h"
#include "Application.h"
#include "shapes.h"
#include "Physics.h"

GravitySimulationScene::GravitySimulationScene(sf::View* view, Application& app) : Scene(app) { // Pass app to base constructor
    this->view = view;
}

void GravitySimulationScene::InitializeObjects() {
    Circle* rectangle = new Circle(50, 100, 0, 0, "obj1");
    rectangle->AddComponent<RigidBody>();
    RigidBody* rb = rectangle->GetComponent<RigidBody>();
    rb->mass = 10000;
    ForceField* forceField = rectangle->AddComponent<ForceField>();
    forceField->body = rb;
    objectsList.push_back(rectangle);
    rectangle->OpenEditor();

    Circle* rectangle1 = new Circle(5, 100, 400, 750, "obj2");
    rectangle1->AddComponent<RigidBody>()->mass = 1;
    RigidBody* rb1 = rectangle1->GetComponent<RigidBody>();
    *rb1->velocity.x = -80;
    rb1->mass = 10;
    ForceField* forceField1 = rectangle1->AddComponent<ForceField>();
    forceField1->body = rb1;
    rectangle1->OpenEditor();
    objectsList.push_back(rectangle1);


    Rectangle* wall1 = new Rectangle(5, 2000, -600, 400, "left");
    wall1->AddComponent<RigidBody>()->stationary = true;
    //objectsList.push_back(wall1);

    Rectangle* wall2 = new Rectangle(5, 2000, 1500, 400, "right");
    wall2->AddComponent<RigidBody>()->stationary = true;
    //objectsList.push_back(wall2);

    Rectangle* wall3 = new Rectangle(2100, 5, 450, -4000, "up");
    wall3->AddComponent<RigidBody>()->stationary = true;
    //objectsList.push_back(wall3);

    Rectangle* wall4 = new Rectangle(2100, 5, 450, 800, "down");
    wall4->AddComponent<RigidBody>()->stationary = true;
    //objectsList.push_back(wall4);

}