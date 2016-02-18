#include "AbstractTool.h"
#include "BezierTool.h"
#include "LineTool.h"
#include "PointerTool.h"
#include "graphics.h"
#pragma once
class Cursor
{
private:
	AbstractTool *current_tool;
	graphics *target;
public:
	bool addPoint(int x, int y);
	Element* finish();
	void reset();
	void useBezierTool();
	void useLineTool();
	void usePointerTool();
	void setColor(int r, int g, int b);

	Element* preview(int x, int y);

	Cursor();
	~Cursor();
};

