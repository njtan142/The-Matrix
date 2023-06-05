#pragma once
#include "SFML/Graphics/Color.hpp"


class Color {
public:
	Color();
	Color(const float r, const float g, const float b);
	Color(const float a, const float r, const float g, const float b);

	sf::Color toSFC();

	float* Array();

public:
	const float* a;
	const float* r;
	const float* g;
	const float* b;

private:
	float arr[4];
};