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
	pixel += sy * this->cw + sx;
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

Color Graphics::rayTrace(Point3 D, float t_min, float t_max)
{
	float closest_t = this->infinity;
	Sphere* closests_sphere = nullptr;
	for (auto& sphere : this->spheres)
	{
		Color c = sphere.getSphereColor();
		float* t_array = sphere.intersectRaySphere(this->camera, D);
		if ((t_array[0] >= t_min && t_array[0] <= t_max) && t_array[0] < closest_t)
		{
			closest_t = t_array[0];
			closests_sphere = &sphere;
		}
		if ((t_array[1] >= t_min && t_array[1] <= t_max) && t_array[1] < closest_t)
		{
			closest_t = t_array[1];
			closests_sphere = &sphere;
		}

	}
	if (closests_sphere == nullptr)
	{
		// should return background color - but i don't have any yet
		// know instead of returning background color it return 
		// color of the first sphere in spheres
		return Color(255, 255, 255);
	};
	return closests_sphere->getSphereColor();
}

void Graphics::render()
{

	for (int x = (-1)*this->cw/2; x < this->cw/2; x++)
	{
		for (int y = (-1) * this->ch / 2; y < this->ch / 2; y++)
		{
			Point3 D = canvasToViewPort(x, y);
			Color color = rayTrace(D, 1, this->infinity);
			this->setPixel(x, y, color.getColor());
		}
	}
}

void Graphics::renderRandomPixels()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 1;
	int max = 0xffffff;
	std::uniform_int_distribution<int> distribution(min, max);
	for (int x = (-1) * this->cw / 2; x < this->cw / 2; x++)
	{
		for (int y = (-1) * this->ch / 2; y < this->ch / 2; y++)
		{
			Color color = Color(distribution(gen));
			this->setPixel(x, y, color.getColor());
		}
	}
}
