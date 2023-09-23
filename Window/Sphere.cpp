#include "Sphere.h"

float* Sphere::intersectRaySphere(Point3 O, Point3 D)
{
	float* t_array = new float[2];

	Point3 CO = O - this->center;

	float a = D.dot(D);
	float b = 2 * CO.dot(D);
	float c = CO.dot(CO) - this->radius*this->radius;

	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		t_array[0] = 1000;
		t_array[1] = 1000;
	}
	else
	{
		t_array[0] = (-b + sqrt(discriminant)) / (2 * a);
		t_array[1] = (-b - sqrt(discriminant)) / (2 * a);
	}

	return t_array;
}