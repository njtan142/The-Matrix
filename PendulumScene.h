#pragma once
#include "Scene.h"
#include "Application.h" // Include Application.h

class PendulumScene : public Scene {
public:
    PendulumScene(sf::View* view, Application& app); // Modified constructor

    void InitializeObjects() override;
};
