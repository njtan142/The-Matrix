#pragma once
#include "SFML/System/Vector2.hpp"
#include <cmath>


class Vector2 {
public:
	float* x;
	float* y;
	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2& other);
	Vector2(sf::Vector2f vector);
	Vector2& operator=(const Vector2& other);
	Vector2 operator*(const Vector2& other);

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;
	float Dot(const Vector2& other) const;
	float Magnitude() const;
	Vector2 Normalized() const;

	sf::Vector2f ToV2F() {
		return sf::Vector2f(*x, *y);
	}

	static Vector2 FromV2F(sf::Vector2f vector) {
		return Vector2(vector.x, vector.y);
	}

	static float Distance(const Vector2& a, const Vector2& b) {
		float dx = *b.x - *a.x;
		float dy = *b.y - *a.y;
		return std::sqrt(dx * dx + dy * dy);
	}

	float* Array();


private:
	float arr[2];
};

