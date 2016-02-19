#pragma once
#include "Element.h"
class PointElement :
	public Element
{
public:
	PointElement();
	PointElement(int x, int y);
	~PointElement();
	void drawSelf(graphics *g);
};

