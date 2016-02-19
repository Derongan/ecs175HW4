#include "LineElement.h"



LineElement::LineElement()
{
	num = 2;
	this->points = new float[4];
	this->show = new int[2];
}

LineElement::LineElement(int x0, int y0, int x1, int y1)
{
	num = 2;
	this->points = new float[4];
	this->show = new int[2];

	points[0] = x0;
	points[1] = y0;
	points[2] = x1;
	points[3] = y1;
}


LineElement::~LineElement()
{
}

void LineElement::drawSelf(graphics * g)
{
	g->setColor(color[0], color[1], color[2]);
	g->bLine(points[0], points[1], points[2], points[3]);
}
