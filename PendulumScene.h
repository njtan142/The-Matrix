#pragma once
#include "Scene.h"

class PendulumScene : public Scene {
public:
	PendulumScene(sf::View* view);

	void InitializeObjects() override;
};