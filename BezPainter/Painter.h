#pragma once
#include "Cursor.h"
#include "DrawStack.h"
class Painter
{
private:
	Cursor *cursor;
	DrawStack *mainStack;
	DrawStack *tempStack;
	graphics *g;
	int x = 0;
	int y = 0;

public:
	Painter(graphics *g);
	~Painter();

	//Update functions
	void draw();
	//Click functions
	void onMouseDown(int button, int state, int x, int y);
	void onMouseUp(int button, int state, int x, int y);
	void onMove(int x, int y);

	//Getter
	Cursor* getCursor();

};

