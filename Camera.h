#pragma once
#include "Transform.h"
#include "Object.h"

class Camera : Object{

public:

	Camera();
	Camera(sf::View view);

	void Follow();

public: 
	Transform position;
	Object* followTarget = nullptr;
	sf::View* view;
};