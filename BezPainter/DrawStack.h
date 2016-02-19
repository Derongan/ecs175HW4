#pragma once
#include "Element.h"
#include "graphics.h"
#include "BezierElement.h"
#include "LineElement.h"
#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

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
	bool push(Element *e);
	bool pop();
	void reset();

	Element* get(int i);
	void set(int i, Element *e);

	void save();
	void load();
};