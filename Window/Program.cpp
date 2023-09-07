#include <iostream>
#include "Window.h"

int main()
{
	std::cout << "Creating window" << std::endl;

	Window* window = new Window();

	window->setBackground(0xdbcdf0);
	for (int i = 0; i < 300; i++)
	{
		for (int j = 0; j < 700; j++)
		{
			window->setPixel(j, i, 0xc6def1);
		}
	}
	window->run();

	std::cout << "Closing window";

	delete window;

	return 0;
}
