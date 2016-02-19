#pragma once
#include "Element.h"
class PointElement :
	public Element
{
public:
	PointElement();
	PointElement(int x, int y);
	~PointElement();
	void draw(graphics *g);
	void drawControlPoints(graphics *g);
};

