#pragma once
#include "Cursor.h"
#include "DrawStack.h"
class Painter
{
private:
	Cursor *cursor;
	DrawStack *mainStack;
	graphics *g;
public:
	Painter(graphics *g);
	~Painter();

	//Click functions
	void onClick(int button, int state, int x, int y);
};

