#include "LineTool.h"

LineTool::LineTool()
{
}


LineTool::~LineTool()
{
}

bool LineTool::addPoint(float x, float y)
{
	this->points[this->pointNumber * 2] = x;
	this->points[this->pointNumber * 2 + 1] = y;
	this->pointNumber++;

	if (pointNumber == 2)
		return false;
	return true;
}

//NOT IMPLEMENTED
Element* LineTool::finish()
{
	return nullptr;
}

void LineTool::reset()
{
	this->pointNumber = 0;
}