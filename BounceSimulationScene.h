#pragma once
#include "Scene.h"
#include "Application.h" // Include Application.h

class BounceSimulationScene : public Scene {
public:
    BounceSimulationScene(sf::View* view, Application& app); // Modified constructor

    void InitializeObjects() override;
};
