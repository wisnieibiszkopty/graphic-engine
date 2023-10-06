#pragma once
#include <cmath>
#include <iostream>

#include "Point3.h"
#include "Color.h"

class Sphere
{
	Point3 center;
	float radius;
	Color color;
public:
	Sphere();
	Sphere(Point3& cntr, float rds, Color& clr);

	Color getSphereColor();
	Point3 getCenter();

	float* intersectRaySphere(Point3 O, Point3 D);

};

