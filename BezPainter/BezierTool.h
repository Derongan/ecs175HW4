#pragma once
#include "AbstractTool.h"
#include "BezierElement.h"
class BezierTool :
	public AbstractTool
{
private:
	float points[20];
	int pointNumber = 0;
	const int MAXPOINTS = 10;
public:
	BezierTool();
	~BezierTool();
	virtual bool addPoint(float x, float y);
	virtual Element* finish();
	virtual void reset();
};

