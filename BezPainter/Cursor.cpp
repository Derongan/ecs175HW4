#include "Cursor.h"



bool Cursor::addPoint(int x, int y)
{
	return current_tool->addPoint(x, y);
}

Element* Cursor::finish()
{
	return current_tool->finish();
}

void Cursor::reset()
{
	current_tool->reset();
}

void Cursor::useBezierTool()
{
	delete current_tool;
	this->current_tool = new BezierTool();
}

void Cursor::useLineTool()
{
	delete current_tool;
	this->current_tool = new LineTool();
}

void Cursor::setTarget(graphics *g)
{
	this->target = g;
}

void Cursor::setColor(int r, int g, int b)
{
	current_tool->setColor(r, g, b);
}

Cursor::Cursor()
{
}


Cursor::~Cursor()
{
}
