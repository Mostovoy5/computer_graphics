#pragma once
#include "Vec3.h"

class Vec4 {
public:
	float x, y, z, f;

	Vec4() { x = 0; y = 0; z = 0; f = 0; }
	Vec4(Vec3 v3) : x(v3.x), y(v3.y), z(v3.z), f(1) {};
	Vec4(float _x, float _y, float _z, float _f) : x(_x), y(_y), z(_z), f(_f) {};

	
	Vec4 operator+(Vec4 const& other) { return Vec4(x + other.x, y + other.y, z + other.z, f + other.f); };
	Vec4 operator-(Vec4 const& other) { return Vec4(x - other.x, y - other.y, z - other.z, f - other.f); };
	Vec4 operator*(Vec4 const& other) { return Vec4(x * other.x, y * other.y, z * other.z, f * other.f); };
	Vec4 operator/(Vec4 const& other) { return Vec4(x / other.x, y / other.y, z / other.z, f / other.f); };

	static Vec3 getVec3(Vec4 v) { return Vec3(v.x, v.y, v.z); }

	float getOne(int i) {
		switch (i)
		{
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		case 3:
			return f;
		default:
			break;
		}
	}

	void addOne(int i, float val) {
		switch (i)
		{
		case 0:
			x += val;
			break;
		case 1:
			y += val;
			break;
		case 2:
			z += val;
			break;
		case 3:
			f += val;
			break;
		default:
			break;
		}
	}

}; 