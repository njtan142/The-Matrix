#pragma once
#include "Scene.h"

class EnergyConservationScene : public Scene {
public:
	EnergyConservationScene(sf::View* view);

	void InitializeObjects() override;
};