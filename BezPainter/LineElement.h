#pragma once
#include "Element.h"
class LineElement :
	public Element
{
private:
public:
	LineElement();
	LineElement(int, int, int, int);
	~LineElement();

	virtual void drawSelf(graphics *g);
	virtual int getClickedControlPoint(float x, float y);
	virtual bool inside(float x, float y);
};

