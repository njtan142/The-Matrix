#pragma once
#include "Scene.h"

class EnergyConservationSceneBilliard : public Scene {
public:
	EnergyConservationSceneBilliard(sf::View* view);

	void InitializeObjects() override;
};