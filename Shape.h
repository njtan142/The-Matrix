#pragma once
#include "SFML/Graphics/RectangleShape.hpp"

#include <string>
#include <memory> // For std::unique_ptr

#include "Vector2.h"
#include "Component.h"
#include "Color.h"


class Shape : public Component {
public:
	Shape() {}
	Shape(Object* entity);
	Shape(std::unique_ptr<sf::Shape> shape, Object* entity);
	Shape(std::unique_ptr<sf::Shape> shape, const std::string& xGeometry, const std::string& yGeometry, std::unique_ptr<Vector2> geometry, Object* entity);

	sf::Shape* Get();
	bool Visible();
	    virtual void RenderEditor() override;
    ~Shape();

	virtual sf::Shape* Get2() {
		return nullptr;
	}

public:
	Vector2 geometry;
	Color color;

protected:
	std::unique_ptr<sf::Shape> shape;
	std::unique_ptr<sf::Shape> shape2;
	std::string xGeometry;
	std::string yGeometry;
	bool visible = false;

};

class DualShape : public Shape {
public:
	DualShape() {}
	DualShape(Object* entity);
	~DualShape();
	DualShape(
		std::unique_ptr<sf::Shape> first_shape,
		std::unique_ptr<sf::Shape> second_shape,
		const std::string& xGeometry,
		const std::string& yGeometry,
		const std::string& xGeometry2,
		const std::string& yGeometry2,
		std::unique_ptr<Vector2> geometry,
		std::unique_ptr<Vector2> geometry2,
		Object* entity
	);

	sf::Shape* Get2() override;

public:
	Vector2 geometry2;

private:
	std::string xGeometry2;
	std::string yGeometry2;
};