#pragma once
#include "AbstractTool.h"
class LineTool :
	public AbstractTool
{
private:
	float points[20];
	int pointNumber = 0;

public:
	LineTool();
	~LineTool();

	virtual void addPoint(float x, float y);
	virtual Element* finish();
	virtual void reset();
};

