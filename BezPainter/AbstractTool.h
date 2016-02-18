#pragma once
#include "Element.h";
class AbstractTool
{
protected:
	float color[3];
public:
	AbstractTool();
	virtual ~AbstractTool();

	virtual void addPoint(float x, float y) = 0;
	virtual Element* finish() = 0;
	virtual void reset() = 0;
	virtual void setColor(float r, float g, float b);
};
