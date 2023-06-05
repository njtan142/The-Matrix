#pragma once
#include "Scene.h"

class GravitySimulationScene : public Scene {
public:
	GravitySimulationScene(sf::View* view);

	void InitializeObjects() override;
};