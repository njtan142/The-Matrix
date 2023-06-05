#include "Camera.h"

Camera::Camera()
{
	position = Transform();
}

Camera::Camera(sf::View view)
{
	sf::Vector2f center= view.getCenter();
	position = Transform(center.x, center.y, 0, this);
	this->view = &view;
}

void Camera::Follow()
{

	if (followTarget == nullptr) {
		return;
	}

	Vector2 followCoord = followTarget->transform->position;
	Vector2 difference = position.position - followCoord;
	view->move(difference.ToV2F());
	position.position = Vector2().FromV2F(view->getCenter());


}

