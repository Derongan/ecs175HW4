#include "Element.h"



Element::Element()
{
	setColor(0, 0, 1);
}


Element::~Element()
{
}

void Element::draw(graphics * g, bool w)
{
	draw(g);
	if (w)
		drawControlPoints(g);
}

void Element::setColor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Element::onMouseDown(int x, int y)
{
}

void Element::drawControlPoints(graphics *g)
{
}

bool Element::inside(float x, float y)
{
	return false;
}

int Element::getClickedControlPoint(float x, float y)
{
	return -1;
}

void Element::translate(float x, float y, int who)
{
}
