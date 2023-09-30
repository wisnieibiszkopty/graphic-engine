#include "Graphics.h"

Graphics::Graphics()
{
	this->infinity = std::numeric_limits<float>::infinity();
}

Graphics::Graphics(void* memory, Point3 c, int cw, int ch)
{
	this->camera = c;
	this->cw = cw;
	this->ch = ch;
	this->vw = 1;
	this->vh = 1;
	this->d = 1;
	this->infinity = std::numeric_limits<float>::infinity();
	this->memory = memory;
}

void Graphics::setPixel(int x, int y, u32 color)
{
	int sx = this->cw / 2 + x;
	int sy = this->ch / 2 - y;
	u32* pixel = (u32*)this->memory;
	pixel += sy * this->ch + sx;
	*pixel = color;
}

void Graphics::addSphereToScene(Sphere& sphere)
{
	this->spheres.push_back(sphere);
}

std::vector<Sphere> Graphics::getSpheres()
{
	return this->spheres;
}

Point3 Graphics::canvasToViewPort(float x, float y) {
	return Point3(x*this->vw/this->cw, y*this->vh/this->ch, d);
}


// tu jest na pewno coœ Ÿle bo zwraca same czarne inie wchodzi w ify
// dobra naprawi³em tak ¿e coœ zwraca
// dobra teraz nawet coœ rysuje ale nigdy nie jest uruchamiany warunek taki ¿eby rysowa³o t³o
Color Graphics::rayTrace(Point3 D, float t_min, float t_max)
{
	float closest_t = this->infinity;
	Sphere* closests_sphere = nullptr;

	bool in = false;

	for (auto & sphere : this->spheres)
	{
		Color c = sphere.getSphereColor();
		float* t_array = sphere.intersectRaySphere(this->camera, D);
		//std::cout << t_array[0] << " " << t_array[1] << std::endl;
		if ((t_array[0] >= t_min && t_array[0] <= t_max) && t_array[0] < closest_t)
		{
			in = true;
			closest_t = t_array[0];
			closests_sphere = &sphere;
			//std::cout << "t1" << std::endl;
		}
		if ((t_array[1] >= t_min || t_array[1] <= t_max) && t_array[1] < closest_t)
		{
			in = true;
			closest_t = t_array[1];
			closests_sphere = &sphere;
			//std::cout << "t2" << std::endl;
		}
		if (in == false) std::cout << "twoja stara" << std::endl;
	}

	//std::cout << closests_sphere << std::endl;

	if (!closests_sphere)
	{
		//std::cout << "background" << std::endl;
		// should return background color - but i don't have any yet
		return Color(0, 0, 0);
	}
	//std::cout << "sphere" << std::endl;
	return closests_sphere->getSphereColor();
}

// pêtla wykonuje siê dobr¹ iloœæ razy

void* Graphics::render()
{

	for (int x = (-1)*this->cw/2; x < this->cw/2; x++)
	{
		for (int y = (-1) * this->ch / 2; y < this->ch / 2; y++)
		{
			Point3 D = canvasToViewPort(x, y);
			Color color = rayTrace(D, 1, this->infinity);
			this->setPixel(x, y, color.getColor());
			//std::cout << color.getColor();
		}
	}
	return this->memory;
}
