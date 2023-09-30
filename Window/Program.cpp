#include <iostream>
#include "Window.h"
#include "Point3.h"
#include "Color.h"
#include "Graphics.h"

int main()
{
	std::cout << "Creating window" << std::endl;

	Window* window = new Window();

	Point3 camera = Point3(0, 0, 0);

	Graphics g = Graphics(window->getMemory(), camera, 900, 500);

	Point3 p1(0, -1, 5);
	//Point3 p2(2, 0, 4);
	//Point3 p3(-2, 0, 4);
	Color c1(255, 0, 0);
	//Color c2(0, 255, 0);
	//Color c3(0, 0, 255);

	Sphere s1 = Sphere(p1, 1.0f, c1);
	//Sphere s2 = Sphere(p2, 1.0f, c2);
	//Sphere s3 = Sphere(p3, 1.0f, c3);

	g.addSphereToScene(s1);
	//g.addSphereToScene(s2);
	//g.addSphereToScene(s3);
	void* memory = g.render();
	window->setMemory(memory);

	window->run();

	std::cout << "Closing window";

	delete window;

	/*
	Point3 p1(1, 3, -5);
	Point3 p2(1, 3, -5);
	std::cout << p1.dot(p2) << std::endl;
	Color c1(124, 43, 109);
	std::cout << std::hex << std::uppercase;
	std::cout << c1.getColor() << std::endl;
	*/

	return 0;
}
