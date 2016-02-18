#include "Painter.h"



Painter::Painter(graphics *g)
{
	mainStack = new DrawStack();
	cursor = new Cursor();
	this->g = g;
}


Painter::~Painter()
{
}

void Painter::onClick(int button, int state, int x, int y)
{
	if (cursor->addPoint(x, y)) {

	}
}
