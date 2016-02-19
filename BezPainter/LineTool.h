#pragma once
#include "AbstractTool.h"
#include "LineElement.h"
#include "PointElement.h"
class LineTool :
	public AbstractTool
{
private:
	float points[20];
	int pointNumber = 0;

public:
	LineTool();
	~LineTool();

	virtual bool onMouseDown(float x, float y);
	virtual Element* finish();
	virtual void reset();
	virtual Element* preview(int x, int y);
};

