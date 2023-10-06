#pragma once
#include <stdint.h>

class Color
{
private:
	uint32_t value;
public:
	Color();
	Color(uint32_t hex_color);
	Color(uint8_t red, uint8_t green, uint8_t blue);

	Color operator*(float number);

	uint32_t getColor();
};

