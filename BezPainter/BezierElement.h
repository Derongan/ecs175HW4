#pragma once
#include "Element.h"
class BezierElement :
	public Element
{
	float points[20];
	unsigned int num;
public:
	BezierElement();
	~BezierElement();
	virtual void draw(graphics *g);
	void setPoints(float* points, int num);
	virtual void addPoint(int x, int y);
	virtual void drawControlPoints(graphics *g);
	virtual bool inside(float x, float y);
};

