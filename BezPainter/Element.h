#pragma once
#include "graphics.h"
class Element;

enum TYPE {
	ELEMENT,
	BEZIER,
	LINE,
};

class Snap {
public:
	Element* who;
	bool front;
	int index;

	Snap(Element* e, bool f, int i) {
		who = e;
		front = f;
		index = i;
	};
	~Snap() {

	};
};

class Element
{
protected:
	int *show;	//Control points to show


	unsigned int num;

public:
	int id = -1;
	Snap **snaps; //BAD MOVE BACK ASAP
	int snapNum = 0;
	float *points; //BAD MOVE BACK ASAP
	float color[3];

	bool snappable = true;

	Element();
	virtual ~Element();
	virtual void draw(graphics *g);
	virtual void drawSelf(graphics *g) = 0;
	virtual void setColor(float r, float g, float b);
	virtual void onMouseDown(int x, int y);
	virtual int onMouseOver(int x, int y);
	virtual bool inside(float x, float y);
	virtual void drawControlPoints(graphics *g);
	virtual int getClickedControlPoint(float x, float y);
	virtual float getPointX(int index);
	virtual float getPointY(int index);
	virtual void setControlPoint(int index, int style);
	virtual void translate(float x, float y, int who);
	virtual TYPE getType();
	virtual int getNum();
	virtual void addSnap(Element* e, bool front, int index);
	virtual void addSnap(Snap* snap);
	virtual void addPoint(float x, float y);
	virtual void updateSnaps();
};

