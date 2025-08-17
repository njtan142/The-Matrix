#pragma once
#include "Scene.h"
#include "Application.h" // Include Application.h

class AccellerationScene : public Scene {
public:
    AccellerationScene(sf::View* view, Application& app); // Modified constructor

    void InitializeObjects() override;
};
