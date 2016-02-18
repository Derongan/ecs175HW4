#include "AbstractTool.h"
#include "BezierTool.h"
#include "LineTool.h"
#include "graphics.h"
#pragma once
class Cursor
{
private:
	AbstractTool *current_tool;
	graphics *target;
public:
	void addPoint(int x, int y);
	Element* finish();
	void reset();
	void useBezierTool();
	void useLineTool();
	void setTarget(graphics *g);
	void setColor(int r, int g, int b);
	Cursor();
	~Cursor();
};

