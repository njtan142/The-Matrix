#include "Shape.h"

DualShape::DualShape(Object* entity) {
	this->entity = entity;
}

DualShape::DualShape(
	std::unique_ptr<sf::Shape> first_shape,
	std::unique_ptr<sf::Shape> second_shape,
	const std::string& xGeometry,
	const std::string& yGeometry,
	const std::string& xGeometry2,
	const std::string& yGeometry2,
	std::unique_ptr<Vector2> geometry,
	std::unique_ptr<Vector2> geometry2,
	Object* entity
) : Shape(std::move(first_shape), xGeometry, yGeometry, std::move(geometry), entity),
	geometry2(*geometry2),
	xGeometry2(xGeometry2),
	yGeometry2(yGeometry2)
{
	this->shape2 = std::move(second_shape);
}

sf::Shape* DualShape::Get2() {
	return shape2.get();
}

DualShape::~DualShape() {
    // Destructor definition
}