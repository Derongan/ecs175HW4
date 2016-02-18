#pragma once
#include "Element.h"
#include "graphics.h"
#include "BezierElement.h"

class DrawStack
{
private:
	Element** _stack;
	Element** _tempStack;
	unsigned int stackSize;
	unsigned int stackLocation;
public:
	DrawStack();
	~DrawStack();
	void draw(graphics *g);
	bool push(Element *e);
	bool pop();
	void reset();
};