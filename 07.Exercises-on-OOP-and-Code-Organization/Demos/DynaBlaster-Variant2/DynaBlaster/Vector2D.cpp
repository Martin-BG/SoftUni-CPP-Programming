#include "Vector2D.h"


Vector2D::Vector2D() : x(0), y(0) { }

Vector2D::Vector2D(double x, double y)
	: x(x)
	, y(y)
{ }

Vector2D Vector2D::operator+(const Vector2D& other) const {
	return Vector2D(this->x + other.x, this->y + other.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
	*this = (*this) + other;
	return *this;
}

Vector2D Vector2D::operator*(const double & factor) const {
	return Vector2D(this->x * factor, this->y * factor);
}

Vector2D& Vector2D::operator*=(const double & factor) {
	*this = (*this) * factor;
	return *this;
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
	return Vector2D(this->x - other.x, this->y - other.y);
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
	*this = (*this) - other;
	return *this;
}

Vector2D Vector2D::operator/(const double & factor) const {
	return Vector2D(this->x / factor, this->y / factor);
}

Vector2D& Vector2D::operator/=(const double & factor) {
	*this = (*this) / factor;
	return *this;
}

bool Vector2D::operator==(const Vector2D & other) const {
	return (this->x == other.x) && (this->y == other.y);
}

bool Vector2D::operator!=(const Vector2D & other) const {
	return !((*this) == other);
}
