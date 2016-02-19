#include "LineTool.h"

LineTool::LineTool()
{
}


LineTool::~LineTool()
{
}

bool LineTool::onMouseDown(float x, float y)
{
	this->points[this->pointNumber * 2] = x;
	this->points[this->pointNumber * 2 + 1] = y;
	this->pointNumber++;

	if (pointNumber == 2)
		return false;
	return true;
}

Element* LineTool::finish()
{
	Element* e = new LineElement(points[0], points[1], points[2], points[3]);
	e->setControlPoint(-1, 0);
	return e;
}

void LineTool::reset()
{
	this->pointNumber = 0;
}

Element * LineTool::preview(int x, int y)
{
	if (pointNumber == 1) {
		return new LineElement(points[0], points[1], x, y);
	}
	else
		return new PointElement(x, y);
}
