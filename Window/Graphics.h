#pragma once
#include <vector>
#include <limits>
#include <stdint.h>
#include <iostream>
#include <random>

#include "Point3.h"
#include "Color.h"
#include "Sphere.h"
#include "Light.h"

typedef uint32_t u32;

/*
	Light computing works great, but i don't know how to store objects which inheritance 
	form Light class in one vector, so i could just call computeIntensity
*/

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
	std::vector<Light *> lights;

	AmbientLight al;
	PointLight pl;

	Graphics();
	Graphics(void* memory, Point3& c, int cw, int ch);

	void setPixel(int x, int y, u32 color);

	// remove later
	void addAmbientLight(AmbientLight& ambientLight);
	void addPointLight(PointLight& pointLight);

	void addSphereToScene(Sphere& sphere);
	void addLight(Light* light);
	std::vector<Sphere> getSpheres();
	std::vector<Light *> getLights();
	Point3 canvasToViewPort(float x, float y);
	float computeLighting(Point3& P, Point3& N);
	Color rayTrace(Point3& D, float t_min, float t_max);
	void render();
	void renderRandomPixels();

};

