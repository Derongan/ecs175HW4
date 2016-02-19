#pragma once
#include "Element.h"
#include "graphics.h"
#include "BezierElement.h"

class DrawStack
{
private:
	Element** _stack;
	unsigned int stackSize;
public:
	unsigned int stackLocation;

	DrawStack();
	~DrawStack();
	void draw(graphics *g);
	void draw(graphics *g, bool w);
	bool push(Element *e);
	bool pop();
	void reset();

	Element* get(int i);
	void set(int i, Element *e);
};