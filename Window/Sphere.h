#pragma once
#include <cmath>

#include "Point3.h"
#include "Color.h"

class Sphere
{
	Point3 center;
	float radius;
	Color color;

	float* intersectRaySphere(Point3 O, Point3 D);
};

