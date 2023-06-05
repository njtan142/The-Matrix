#include "Vector2.h"
#include <cmath>

Vector2::Vector2() : arr{ 0.0f, 0.0f }, x(&arr[0]), y(&arr[1]) {}

Vector2::Vector2(float x, float y) : arr{ x, y }, x(&arr[0]), y(&arr[1]) {}

Vector2::Vector2(const Vector2& other) : arr{ *other.x, *other.y }, x(&arr[0]), y(&arr[1]) {}

Vector2::Vector2(sf::Vector2f vector)
{
    arr[0] = vector.x;
    arr[1] = vector.y;

    x = &arr[0];
    y = &arr[0];
}

Vector2& Vector2::operator=(const Vector2& other) {
	arr[0] = *other.x;
	arr[1] = *other.y;
    x = &arr[0];
    y = &arr[1];
	return *this;
}

Vector2 Vector2::operator*(const Vector2& other) {
	return Vector2(*x * *other.x, *y * *other.y);
}

float* Vector2::Array() {
	return arr;
}



Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2(arr[0] + other.arr[0], arr[1] + other.arr[1]);
}

Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2(arr[0] - other.arr[0], arr[1] - other.arr[1]);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(arr[0] * scalar, arr[1] * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    return Vector2(arr[0] / scalar, arr[1] / scalar);
}

float Vector2::Dot(const Vector2& other) const {
    return arr[0] * other.arr[0] + arr[1] * other.arr[1];
}

float Vector2::Magnitude() const {
    return std::sqrt(arr[0] * arr[0] + arr[1] * arr[1]);
}

Vector2 Vector2::Normalized() const {
    float mag = Magnitude();
    if (mag != 0.f) {
        return Vector2(arr[0] / mag, arr[1] / mag);
    }
    else {
        return Vector2();
    }
}