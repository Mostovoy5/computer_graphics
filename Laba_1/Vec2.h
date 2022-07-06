#pragma once

class Vec2
{
public:
	float x, y;

	Vec2(float other) : x(other), y(other){};
	Vec2(float pointX, float pointY) : x(pointX), y(pointY) {};

	Vec2 operator+(Vec2 const& other) { return Vec2(x + other.x, y + other.y); };
	Vec2 operator-(Vec2 const& other) { return Vec2(x - other.x, y - other.y); };
	Vec2 operator*(Vec2 const& other) { return Vec2(x * other.x, y * other.y); };
	Vec2 operator/(Vec2 const& other) { return Vec2(x / other.x, y / other.y); };
};

