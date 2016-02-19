#pragma once
#include "AbstractTool.h"
#include "BezierElement.h"
class BezierTool :
	public AbstractTool
{
private:
	float points[20];
	int pointNumber = 0;
	const int MAXPOINTS = 3;
public:
	BezierTool();
	~BezierTool();
	virtual bool onMouseDown(float x, float y);
	virtual Element* finish();
	virtual void reset();
	virtual Element* preview(int x, int y);
};

