#include "Color.h"

Color::Color()
{

}

Color::Color(uint32_t hex_color) {
	this->value = hex_color;
}

Color::Color(uint8_t red, uint8_t green, uint8_t blue)
{
	// I don't know how it suppose to work, but it convert rgb to hexdecimal
	this->value = ((uint32_t)red << 16) | ((uint32_t)green << 8) | blue;
}

Color Color::operator*(float number)
{
    uint8_t red = (this->getColor() >> 16) & 0xFF;
    uint8_t green = (this->getColor() >> 8) & 0xFF;
    uint8_t blue = this->getColor() & 0xFF;

    red = static_cast<uint8_t>(red * number);
    green = static_cast<uint8_t>(green * number);
    blue = static_cast<uint8_t>(blue * number);

    return (static_cast<uint32_t>(red) << 16) | (static_cast<uint32_t>(green) << 8) | static_cast<uint32_t>(blue);
}

uint32_t Color::getColor() {
	return this->value;
}