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
	void draw(graphics *g);
	void setPoints(float* points, int num);
};

