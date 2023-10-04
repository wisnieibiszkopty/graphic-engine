#include <iostream>
#include "Window.h"
#include "Point3.h"
#include "Color.h"
#include "Graphics.h"

/*
	There are two major problems with rendering spheres:
	1. If i use resolution higher than 600x400 app will brake
	2. Background has color of ball which is at 1. index in list

	1. has something to do with VirtualAlloc, i replace 4 with 8 and its working
	good, but i don't know how much memory should i alloc at all

	also 800x800 isn't rendering all now
*/

int main()
{
	std::cout << "Creating window" << std::endl;

	int width = 800;
	int height = 600;

	Window* window = new Window(width, height);

	Point3 camera = Point3(0, 0, 0);

	Graphics g = Graphics(window->getMemory(), camera, width, height);

	Point3 p1(-2, -1, 3);
	Point3 p2(2, -0.5, 4);
	Point3 p3(-2, 0, 4);
	Point3 p4(0, 1, 7);

	Color c1(255, 0, 0);
	Color c2(0, 255, 0);
	Color c3(0, 0, 255);
	Color c4(0, 0, 0);

	Sphere s1 = Sphere(p1, 1.0f, c1);
	Sphere s2 = Sphere(p2, 1.0f, c2);
	Sphere s3 = Sphere(p3, 1.0f, c3);
	Sphere s4 = Sphere(p4, 1.0f, c4);

	g.addSphereToScene(s4);
	g.addSphereToScene(s2);
	g.addSphereToScene(s3);
	g.addSphereToScene(s1);
	g.render();

	window->run();

	std::cout << "Closing window";

	delete window;

	return 0;
}
