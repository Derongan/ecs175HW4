#pragma once
#include "Element.h";
#include "DrawStack.h"
class AbstractTool
{
protected:
	float color[3];
	DrawStack* stack;
public:
	AbstractTool();
	virtual ~AbstractTool();

	virtual bool onMouseDown(float x, float y) = 0;
	virtual Element* finish() = 0;
	virtual void reset() = 0;
	virtual void setColor(float r, float g, float b);
	virtual Element* preview(int x, int y);
	virtual void onMouseUp(float x, float y);
	void setStack(DrawStack* stack);
};

