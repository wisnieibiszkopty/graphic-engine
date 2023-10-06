#pragma once
#include "Point3.h"

class Light {
protected:
	float intensity;

	Light() {}
	Light(float i) : intensity(i) {
		if (i > 1.0f) intensity = 1.0f;
		if (i < 0.0f) intensity = 0.0f;
	}
public:
	virtual ~Light() {}
	float computeIntensity(Point3 P, Point3 N) { return 0.0f; };
};

class AmbientLight : Light {
public:
	AmbientLight() {}
	AmbientLight(float i) : Light(i) {}

	float computeIntensity(Point3 P, Point3 N)
	{
		return this->intensity;
	};
};

class PointLight : Light {
private:
	Point3 position;
public:
	PointLight() {}
	PointLight(float i, Point3 p) : Light(i), position(p) {}

	// add length of vector and comparsion operator

	float computeIntensity(Point3 P, Point3 N)
	{
		Point3 L = this->position - P;
		float n_dot_l = N.dot(L);
		if (n_dot_l > 0)
		{
			return this->intensity * n_dot_l / (N.length() * L.length());
		}
		return 0.0f;
	};

};

class DirectionalLight : Light {
private:
	Point3 direction;
public:
	DirectionalLight(float i, Point3 d) : Light(i), direction(d) {}

	float computeIntensity(Point3 P, Point3 N)
	{
		Point3 L = this->direction;
		float n_dot_l = N.dot(L);
		if (n_dot_l > 0)
		{
			return this->intensity * n_dot_l / (N.length() * L.length());
		}
		return 0.0f;
	};
};