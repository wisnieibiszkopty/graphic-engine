#include <iostream>
#include "Window.h"
#include "Point3.h"

int main()
{
	/*std::cout << "Creating window" << std::endl;

	float cameraPosition[3] = { 0., 0., 0. };

	Window* window = new Window();

	window->setBackground(0xdbcdf0);
	window->drawRect(50, 50, 1000, 200, 0xc6def1);
	window->run();

	std::cout << "Closing window";

	delete window;*/

	Point3 p1(1, 3, -5);
	Point3 p2(1, 3, -5);
	std::cout << p1.dot(p2) << std::endl;
	

	return 0;
}
