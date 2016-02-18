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

void PointElement::drawControlPoints(graphics * g)
{
	for (int j = 0; j < 7; j++) {
		g->setPixel(x + j - 3, y + 3);
		g->setPixel(x + j - 3, y - 3);
		g->setPixel(x - 3, y + j - 3);
		g->setPixel(x + 3, y + j - 3);
	}
}
