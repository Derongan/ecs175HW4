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

void Cursor::usePointerTool()
{
	delete current_tool;
	PointerTool *e = new PointerTool();
	e->setStack(stack);
	current_tool = e;
}

void Cursor::setColor(int r, int g, int b)
{
	current_tool->setColor(r, g, b);
}

Element * Cursor::preview(int x, int y)
{
	if(current_tool != nullptr)
		return current_tool->preview(x,y);
	return nullptr;
}

Cursor::Cursor(DrawStack *stack)
{
	this->stack = stack;
}


Cursor::~Cursor()
{
}
