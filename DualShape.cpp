#include "Shape.h"

DualShape::DualShape(Object* entity) {
	this->entity = entity;
}

DualShape::DualShape(
	sf::Shape* first_shape,
	sf::Shape* second_shape,
	const std::string& xGeometry,
	const std::string& yGeometry,
	const std::string& xGeometry2,
	const std::string& yGeometry2,
	const Vector2* geometry,
	const Vector2* geometry2,
	Object* entity
) {

	this->shape = first_shape;
	this->shape2 = second_shape;
	this->xGeometry = xGeometry;
	this->xGeometry2 = xGeometry2;
	this->yGeometry = yGeometry;
	this->yGeometry2 = yGeometry2;
	this->geometry = *geometry;
	this->geometry2 = *geometry2;
	this->entity = entity;
}

sf::Shape* DualShape::Get2() {
	return shape2;
}