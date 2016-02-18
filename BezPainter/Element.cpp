#include "Element.h"



Element::Element()
{
	setColor(0, 0, 1);
}


Element::~Element()
{
}

void Element::setColor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Element::addPoint(int x, int y)
{
}

void Element::drawControlPoints(graphics *g)
{
}
