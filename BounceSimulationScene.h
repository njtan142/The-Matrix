#pragma once
#include "Scene.h"

class BounceSimulationScene : public Scene {
public:
	BounceSimulationScene(sf::View* view);

	void InitializeObjects() override;
};