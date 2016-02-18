#pragma once
#include "Element.h"
class PointElement :
	public Element
{
private:
	int x;
	int y;
public:
	PointElement();
	PointElement(int x, int y);
	~PointElement();
	void draw(graphics *g);
	void drawControlPoints(graphics *g);
};

