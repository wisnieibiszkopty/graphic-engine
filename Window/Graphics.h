#pragma once
#include <vector>
#include <limits>
#include <stdint.h>
#include <iostream>
#include <random>

#include "Point3.h"
#include "Color.h"
#include "Sphere.h"

//
//	I need Scene - object which will store information about objects
//	for this moment i will use simply vector to store list of spheres
//  What if this class would become Scene?
//

typedef uint32_t u32;

class Graphics
{
public:
	float vw;
	float vh;
	int cw;
	int ch;
	float d;
	float infinity;

	void* memory;

	Point3 camera = Point3(0, 0, 0);
	std::vector<Sphere> spheres;

	Graphics();
	Graphics(void* memory, Point3 c, int cw, int ch);

	void setPixel(int x, int y, u32 color);

	void addSphereToScene(Sphere& sphere);
	std::vector<Sphere> getSpheres();
	Point3 canvasToViewPort(float x, float y);
	Color rayTrace(Point3 D, float t_min, float t_max);
	void render();
	void renderRandomPixels();

};

