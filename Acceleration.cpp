#include "Physics.h"

Acceleration::Acceleration() : direction(Vector2(0.f, 0.f)), magnitude(0.f) {}

Acceleration::Acceleration(float dx, float dy, float magnitude) : direction(Vector2(dx, dy)), magnitude(magnitude) {}

