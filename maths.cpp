#include "stdafx.h"
#include "maths.h"

#define PI 3.14159f

float sfld::maths::toRadians(float degrees) {
	return degrees * (PI / 180);
}

float sfld::maths::toDegrees(float radians) {
	return radians * (180 / PI);
}