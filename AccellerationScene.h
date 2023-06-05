#pragma once
#include "Scene.h"

class AccellerationScene : public Scene {
public:
	AccellerationScene(sf::View* view);

	void InitializeObjects() override;
};