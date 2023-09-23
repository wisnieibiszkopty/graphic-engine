#pragma once
#include <string>

class Point3
{
public:

	float x;
	float y;
	float z;

	Point3(float x_p, float y_p, float z_p);

	float getX();
	float getY();
	float getZ();

	float dot(Point3& point);

	Point3 operator+(Point3& otherPoint);
	Point3 operator-(Point3& otherPoint);

};

