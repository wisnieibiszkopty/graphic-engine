#pragma once
#include "Point3.h"

// make Point2

class Graphics
{
	float vw;
	float vh;
	float cw;
	float ch;
	float d;

	Point3 canvasToViewPort(float x, float y);
};

