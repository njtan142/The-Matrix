#pragma once
#include "Scene.h"
#include "Application.h" // Include Application.h

class EnergyConservationSceneBilliard : public Scene {
public:
    EnergyConservationSceneBilliard(sf::View* view, Application& app); // Modified constructor

    void InitializeObjects() override;
};
