#pragma once
#include "Vec3.h"

class Sphere {
public:
	float x, y, z, r;

	Sphere(float _x, float _y, float _z, float _r): x(_x), y(_y), z(_z), r(_r) {}
	Vec3 giveCenter() {
		return (x, y, z);
	}
	float giveRadius() {
		return r;
	}
};