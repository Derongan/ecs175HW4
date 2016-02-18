#pragma once
#include "AbstractTool.h"
class EditTool :
	public AbstractTool
{
public:
	EditTool();
	~EditTool();

	virtual bool addPoint(float x, float y);
	virtual Element* finish();
	virtual void reset();
};

