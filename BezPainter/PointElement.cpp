#include "PointElement.h"



PointElement::PointElement()
{
	this->points = new float[2];
}

PointElement::PointElement(int x, int y)
{
	this->points = new float[2];
	this->points[0] = x;
	this->points[1] = y;
}


PointElement::~PointElement()
{
}

void PointElement::draw(graphics *g)
{
	g->setColor(color[0], color[1], color[2]);
	g->setPixel(points[0], points[1]);
}

void PointElement::drawControlPoints(graphics * g)
{
	for (int j = 0; j < 7; j++) {
		g->setPixel(points[0] + j - 3, points[1] + 3);
		g->setPixel(points[0] + j - 3, points[1] - 3);
		g->setPixel(points[0] - 3, points[1] + j - 3);
		g->setPixel(points[0] + 3, points[1] + j - 3);
	}
}
