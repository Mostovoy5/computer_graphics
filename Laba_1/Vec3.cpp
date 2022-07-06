#pragma once
#include <iostream>
#include <math.h>
#include "Vec3.h"
#include "Vec2.h"
#include "Sphere.cpp"


float Vec3::length(Vec3 v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
Vec3 Vec3::norm(Vec3 v){ return v / length(v); }
float Vec3::dot(Vec3 vec1, Vec3 vec2) { return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z; }
float Vec3::clamp(float value, float min, float max) { return fmax(min,fmin(max, value)); }
Vec3 Vec3::crossProduct(Vec3 vec1, Vec3 vec2)
{
	return Vec3(vec1.y * vec2.z - vec1.z * vec2.y,
				vec1.z * vec2.x - vec1.x * vec2.z,
				vec1.x * vec2.y - vec1.y * vec2.x);
}

Vec3 Vec3::rotateY(Vec3 a, double angle)
{
	Vec3 b = a;
	b.x = a.x * cos(angle) - a.z * sin(angle);
	b.z = a.x * sin(angle) + a.z * cos(angle);
	return b;
}
Vec3 Vec3::rotateZ(Vec3 a, double angle)
{
	Vec3 b = a;
	b.x = a.x * cos(angle) - a.y * sin(angle);
	b.y = a.x * sin(angle) + a.y * cos(angle);
	return b;
}

float Vec3::sphereIntersection(Vec3 origin, Vec3 dir, Vec3 center, float radius) {
	Vec3 o = origin;
	Vec3 ce = center;
	Vec3 k = o - ce;
	Vec3 d = dir;

	float d2 = dot(d, d);
	float r2 = radius * radius;
	float k2 = dot(k, k);

	float a = d2;
	float b = 2 * dot(d, k);
	float c = k2 - r2;

	float D = b * b - 4 * a * c;
	return D >= 0;
} 
float Vec3::planeIntersection(Vec3 origin, Vec3 dir, Vec3 p, float w) {
	return -(dot(origin, p) + w) / dot(dir, p);
}
Vec2 Vec3::sphereIntersectionPlus(Vec3 origin, Vec3 dir, float r) {
	float b = dot(origin, dir);
	float c = dot(origin, origin) - r * r;
	float h = b * b - c;
	if (h < 0.0) return Vec2(-1.0);
	h = sqrt(h);
	return Vec2(-b - h, -b + h);
}

float Vec3::triangle_intersection(Vec3 origin, Vec3 dir, Vec3 v0, Vec3 v1, Vec3 v2) {
	Vec3 e1 = v1 - v0;
	Vec3 e2 = v2 - v0;
	// Вычисление вектора нормали к плоскости
	Vec3 pvec = crossProduct(dir, e2);
	float det = dot(e1, pvec);

	// Луч параллелен плоскости
	if (det < 1e-8 && det > -1e-8) {
		return 0;
	}

	float inv_det = 1 / det;
	Vec3 tvec = origin - v0;
	float u = dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) {
		return 0;
	}

	Vec3 qvec = crossProduct(tvec, e1);
	float v = dot(dir, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return 0;
	}
	return dot(e2, qvec) * inv_det;
}