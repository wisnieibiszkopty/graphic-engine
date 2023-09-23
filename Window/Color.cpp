#include "Color.h"

Color::Color(uint32_t value) {
	this->value = value;
}

uint32_t Color::getColor() {
	return this->value;
}