#include "LineElement.h"



LineElement::LineElement()
{
	num = 2;
	id = curid++;

	this->points = new float[4];
	this->show = new int[2];
}

LineElement::LineElement(int x0, int y0, int x1, int y1)
{
	num = 2;
	id = curid++;

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

int LineElement::getClickedControlPoint(float x, float y)
{
	for (int i = 0; i < num; i++) {
		int x1 = points[i * 2];
		int y1 = points[i * 2 + 1];

		if (x - 4 < x1 && x + 4 > x1 && y - 4 < y1 && y + 4 > y1)
			return i;
	}
	return -1;
}

bool LineElement::inside(float x, float y)
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

	return (x - 4 < maxX && x + 4 > minX && y - 4 < maxY && y + 4 > minY);
}