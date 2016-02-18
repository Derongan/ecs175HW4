#include "BezierElement.h"



BezierElement::BezierElement()
{
}


BezierElement::~BezierElement()
{
}

void BezierElement::draw(graphics *g)
{
	g->setColor(color[0], color[1], color[2]);
	g->bezier(this->points, this->num);
}

void BezierElement::setPoints(float * points, int num)
{
	for (int i = 0; i < num*2; i++) {
		this->points[i] = points[i];
	}
	this->num = num;
}

void BezierElement::addPoint(int x, int y)
{
	if (num >= 20)
		return;

	points[num * 2] = x;
	points[num * 2 + 1] = y;
	num++;
}

void BezierElement::drawControlPoints(graphics *g)
{
	for (int i = 0; i < num; i++) {
		g->setColor(0, 1, 0);
		g->setPixel(points[i * 2], points[i * 2 + 1]);
	}
}
