#include "BezierTool.h"



BezierTool::BezierTool()
{
}

BezierTool::~BezierTool()
{
}

bool BezierTool::addPoint(float x, float y)
{
	this->points[this->pointNumber*2] = x;
	this->points[this->pointNumber*2 + 1] = y;
	this->pointNumber++;
	if (pointNumber > MAXPOINTS)
		return false;
	return true;
}

Element* BezierTool::finish()
{
	BezierElement *e = new BezierElement();
	e->setPoints(points, pointNumber);
	e->setColor(color[0], color[1], color[2]);
	return e;
}

void BezierTool::reset()
{
	this->pointNumber = 0;
}