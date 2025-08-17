#pragma once
#include "Scene.h"
#include "Application.h" // Include Application.h

class EnergyConservationScene : public Scene {
public:
    EnergyConservationScene(sf::View* view, Application& app); // Modified constructor

    void InitializeObjects() override;
};
