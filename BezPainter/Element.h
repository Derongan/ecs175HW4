#pragma once
#include "graphics.h"
class Element
{
protected:
	float color[3];
public:
	Element();
	virtual ~Element();
	virtual void draw(graphics *g) = 0;
	virtual void draw(graphics *g, bool w);
	virtual void setColor(float r, float g, float b);
	virtual void addPoint(int x, int y);
	virtual void drawControlPoints(graphics *g);
};

