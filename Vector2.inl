using namespace sfld;

template<typename T>
Vector2<T>::Vector2() {
	x = 0;
	y = 0;
}

template<typename T>
Vector2<T>::Vector2(T X, T Y) {
	x = X;
	y = Y;
}

template<typename T>
Vector2<T>::Vector2(const sf::Vector2<T>& vector) {
	x = vector.x;
	y = vector.y;
}

template<typename T>
Vector2<T> Vector2<T>::rotate(float degrees) {
	float radians = maths::toRadians(degrees);
	Vector2<T> rotated;
	rotated.x = x * cos(angle) + y * sin(angle);
	rotated.y = -point.x * sin(angle) + point.y * cos(angle);
	return rotated;
}

template<typename T>
Vector2<T> Vector2<T>::rotate(float degrees, const Vector2<T>& origin) {
	float radians = maths::toRadians(degrees);
	Vector2<T> difference = *this - origin;
	Vector2<T> rotated;
	rotated.x = difference.x * cos(radians) + difference.y * sin(radians);
	rotated.y = -difference.x * sin(radians) + difference.y * cos(radians);
	return rotated;
}

template<typename T>
float Vector2<T>::dot(const Vector2<T>& other) const {
	return (x * other.x) + (y * other.y);
}

template<typename T>
Vector2<T> Vector2<T>::normalise() const {
	float len = length();
	if (len == 0) return Vector2<T>(0, 0);
	return Vector2<T>(x / len, y / len);
}

template<typename T>
float Vector2<T>::length() const {
	return sqrt(x*x + y*y);
}

template<typename T>
Vector2<T> Vector2<T>::perpendicular() const {
	return Vector2<T>(-y, x);
}

template<typename T>
Vector2<T> Vector2<T>::lerp(const Vector2<T>& start, const Vector2<T>& end, float percent) const {
	return start + percent*(end - start);
}

template<typename T>
Vector2<T> Vector2<T>::negate() const {
	return Vector2<T>(-x, -y);
}