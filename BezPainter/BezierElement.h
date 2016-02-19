#pragma once
#include "Element.h"
class BezierElement :
	public Element
{
public:
	BezierElement();
	~BezierElement();
	virtual void drawSelf(graphics *g);
	void setPoints(float* points, int num);
	virtual void onMouseDown(int x, int y);
	virtual bool inside(float x, float y);
	virtual int getClickedControlPoint(float x, float y);
	virtual void translate(float x, float y, int who);
	virtual void snap(Element* e, int index);
	virtual TYPE getType();
	virtual void updateSnaps();
};

