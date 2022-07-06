#pragma once
#include "Vec2.h"

class Vec3 {
public:
	float x, y, z;

	Vec3() : x(0), y(0), z(0) {};
	Vec3(float other) : x(other), y(other), z(other) {};
	Vec3(float pointX, float pointY, float pointZ) : x(pointX), y(pointY), z(pointZ) {};

	Vec3 operator+(Vec3 const& other) { return Vec3(x + other.x, y + other.y, z + other.z); };
	Vec3 operator-(Vec3 const& other) { return Vec3(x - other.x, y - other.y, z - other.z); };
	Vec3 operator*(Vec3 const& other) { return Vec3(x * other.x, y * other.y, z * other.z); };
	Vec3 operator/(Vec3 const& other) { return Vec3(x / other.x, y / other.y, z / other.z); };

	static float sphereIntersection(Vec3 ro1, Vec3 rd1, Vec3 center, float radius);
	static float length(Vec3 v);
	static Vec3 norm(Vec3 v);
	static float dot(Vec3 v1, Vec3 v2);
	static float clamp(float value, float min, float max);
	static Vec3 crossProduct(Vec3 vec1, Vec3 vec2);
	static Vec3 rotateY(Vec3 a, double angle);
	static Vec3 rotateZ(Vec3 a, double angle);
	static float planeIntersection(Vec3 ro, Vec3 rd, Vec3 p, float w);
	static Vec2 sphereIntersectionPlus(Vec3 ro, Vec3 rd, float r);
	static float triangle_intersection(Vec3 orig, Vec3 dir, Vec3 v0, Vec3 v1, Vec3 v2);
};

