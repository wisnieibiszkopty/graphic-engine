#include "Point3.h"

Point3::Point3()
{

}

Point3::Point3(float x_p, float y_p, float z_p) {
	this->x = x_p;
	this->y = y_p;
	this->z = z_p;
}

float Point3::getX() {
	return this->x;
}

float Point3::getY() {
	return this->y;
}

float Point3::getZ() {
	return this->z;
}

float Point3::length()
{
	return sqrt(pow(this->getX(), 2) + pow(this->getY(), 2) + pow(this->getZ(), 2));
}

float Point3::dot(Point3& point)
{
	return (this->getX() * point.getX()) + (this->getY() * point.getY()) + (this->getZ() * point.getZ());
}

Point3 Point3::operator+(Point3& otherPoint) 
{
	return Point3(this->x + otherPoint.getX(), this->y + otherPoint.getY(), this->z + otherPoint.getZ());
}

Point3 Point3::operator-(Point3& otherPoint)
{
	return Point3(this->x - otherPoint.getX(), this->y - otherPoint.getY(), this->z - otherPoint.getZ());
}

Point3 Point3::operator*(float number)
{
	return Point3(this->getX() * number, this->getY() * number, this->getZ() * number);
}

Point3 Point3::operator/(float number)
{
	return Point3(this->getX() / number, this->getY() / number, this->getZ() / number);
}