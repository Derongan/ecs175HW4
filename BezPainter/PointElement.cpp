#include "PointElement.h"



PointElement::PointElement()
{
}

PointElement::PointElement(int x, int y)
{
	this->x = x;
	this->y = y;
}


PointElement::~PointElement()
{
}

void PointElement::draw(graphics *g)
{
	g->setColor(color[0], color[1], color[2]);
	g->setPixel(x, y);
}
