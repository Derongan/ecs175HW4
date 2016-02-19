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
		for (int j = 0; j < 7; j++) {
			g->setPixel(points[i * 2] + j - 3, points[i * 2 + 1] + 3);
			g->setPixel(points[i * 2] + j - 3, points[i * 2 + 1] - 3);
			g->setPixel(points[i * 2] - 3, points[i * 2 + 1] + j - 3);
			g->setPixel(points[i * 2] + 3, points[i * 2 + 1] + j - 3);
		}
	}
}

bool BezierElement::inside(float x, float y)
{
	float maxX, maxY, minX, minY;
	maxX = minX = points[0];
	minY = maxY = points[1];

	for (int i = 1; i < num; i++) {
		maxX = fmax(maxX, points[2 * i]);
		maxY = fmax(maxY, points[2 * i + 1]);
		minX = fmin(minX, points[2 * i]);
		minY = fmin(minY, points[2 * i + 1]);
	}

	return (x - 3 < maxX && x + 3 > minX && y - 3 < maxY && y + 3 > minY);
}
