#pragma once
#include "graphics.h"
class Element
{
protected:
	float color[3];
	float *points;
public:
	Element();
	virtual ~Element();
	virtual void draw(graphics *g) = 0;
	virtual void draw(graphics *g, bool w);
	virtual void setColor(float r, float g, float b);
	virtual void onMouseDown(int x, int y);
	virtual void onMouseOver(int x, int y);
	virtual void drawControlPoints(graphics *g);
	virtual bool inside(float x, float y);
	virtual int getClickedControlPoint(float x, float y);
	virtual void translate(float x, float y, int who);
};

