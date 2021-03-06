#pragma once
#include "AbstractTool.h"

class PointerTool :
	public AbstractTool
{
private:
	Element* e = nullptr;
	int index = -1;
	float lx;
	float ly;
	bool down = false;
	int pind = -1;
	bool movingPt = false;

public:
	PointerTool();
	~PointerTool();
	virtual bool onMouseDown(float x, float y);
	virtual void onMouseUp(float x, float y);
	virtual Element* finish();
	virtual void reset();
	virtual void setColor(float r, float g, float b);

	virtual Element* preview(int x, int y);

	void replaceElement();
};

