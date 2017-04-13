#pragma once
class Vector2D
{
public:
	int x;
	int y;

	Vector2D();

	Vector2D(double x, double y);

	Vector2D operator+(const Vector2D& other) const;

	Vector2D& operator+=(const Vector2D& other);

	Vector2D operator*(const double & factor) const;

	Vector2D& operator*=(const double & factor);

	Vector2D operator-(const Vector2D& other) const;

	Vector2D& operator-=(const Vector2D& other);

	Vector2D operator/(const double & factor) const;

	Vector2D& operator/=(const double & factor);

	bool operator==(const Vector2D & other) const;

	bool operator!=(const Vector2D & other) const;

};

