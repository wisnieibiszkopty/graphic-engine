#include "Graphics.h"

Point3 Graphics::canvasToViewPort(float x, float y) {
	return Point3(x*this->vw/this->cw, y*this->vh/this->ch, d);
}
