#pragma once
#include "AbstractTool.h"
class PointerTool :
	public AbstractTool
{
public:
	PointerTool();
	~PointerTool();
	virtual bool addPoint(float x, float y);
	virtual Element* finish();
	virtual void reset();
	virtual void setColor(float r, float g, float b);
};

