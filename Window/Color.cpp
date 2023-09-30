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

uint32_t Color::getColor() {
	return this->value;
}