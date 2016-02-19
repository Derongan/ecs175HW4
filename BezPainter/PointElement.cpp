#include "PointElement.h"



PointElement::PointElement()
{
	id = curid++;

	num = 1;
	this->points = new float[2];
	this->show = new int[1];
}

PointElement::PointElement(int x, int y)
{
	id = curid++;

	num = 1;
	this->points = new float[2];
	this->show = new int[1];

	this->points[0] = x;
	this->points[1] = y;
}


PointElement::~PointElement()
{
}

void PointElement::drawSelf(graphics *g)
{
	g->setColor(color[0], color[1], color[2]);
	g->setPixel(points[0], points[1]);
}
