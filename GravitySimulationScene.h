#pragma once
#include "Scene.h"
#include "Application.h" // Include Application.h

class GravitySimulationScene : public Scene {
public:
    GravitySimulationScene(sf::View* view, Application& app); // Modified constructor

    void InitializeObjects() override;
};
