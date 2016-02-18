#pragma once
#include "Element.h"
class LineElement :
	public Element
{
private:
	float points[4];
public:
	LineElement();
	LineElement(int, int, int, int);
	~LineElement();

	virtual void draw(graphics *g);
	virtual void drawControlPoints(graphics *g);
};

