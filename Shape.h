#pragma once
#include "SFML/Graphics/RectangleShape.hpp"

#include <string>

#include "Vector2.h"
#include "Component.h"
#include "Color.h"


class Shape : public Component {
public:
	Shape() {}
	Shape(Object* entity);
	Shape(sf::Shape* shape, Object* entity);
	Shape(sf::Shape* shape, const std::string& xGeometry, const std::string& yGeometry, const Vector2* geometry, Object* entity);

	sf::Shape* Get();
	bool Visible();
	void RenderEditor() override;

	virtual sf::Shape* Get2() {
		return nullptr;
	}

public:
	Vector2 geometry;
	Color color;

protected:
	sf::Shape* shape = nullptr;
	sf::Shape* shape2 = nullptr;
	std::string xGeometry;
	std::string yGeometry;
	bool visible = false;

};

class DualShape : public Shape {
public:
	DualShape() {}
	DualShape(Object* entity);
	DualShape(
		sf::Shape* first_shape,
		sf::Shape* second_shape,
		const std::string& xGeometry,
		const std::string& yGeometry,
		const std::string& xGeometry2,
		const std::string& yGeometry2,
		const Vector2* geometry,
		const Vector2* geometry2,
		Object* entity
	);

	sf::Shape* Get2() override;

public:
	Vector2 geometry2;

private:
	std::string xGeometry2;
	std::string yGeometry2;
};