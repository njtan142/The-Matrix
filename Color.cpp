#include "Color.h"



Color::Color() : arr{ 1.f, 1.f, 1.f, 1.f }, a(&arr[3]), r(&arr[0]), g(&arr[1]), b(&arr[2]) {}

Color::Color(const float r, const float g, const float b) :
	arr{ 1.f, 1.f, 1.f, 1.f }, a(&arr[3]), r(&arr[0]), g(&arr[1]), b(&arr[2]) {}

Color::Color(const float a, const float r, const float g, const float b) :
	arr{ a, r, g, b }, a(&arr[3]), r(&arr[0]), g(&arr[1]), b(&arr[2]) {

}


sf::Color Color::toSFC() {

	return sf::Color(
		static_cast<sf::Uint8>(*r * 255.f),
		static_cast<sf::Uint8>(*g * 255.f),
		static_cast<sf::Uint8>(*b * 255.f),
		static_cast<sf::Uint8>(*a * 255.f)
	);
}


float* Color::Array() {
	return arr;
}

