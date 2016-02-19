#include "Cursor.h"



bool Cursor::onMouseDown(int x, int y)
{
	if (snap) {
		x = snapX;
		y = snapY;
		int res = current_tool->snap(partner, snapID);
		if (res == 1) {
			frontSnap = new Snap(partner, true, snapID);
			return true;
		}
		else if (res == 2) {
			tailSnap = new Snap(partner, false, snapID);
		}
	}
	return current_tool->onMouseDown(x, y);
}

void Cursor::onMouseUp(int x, int y)
{
	current_tool->onMouseUp(x, y);
}

Element* Cursor::finish()
{
	Element *e = current_tool->finish();
	if (frontSnap != nullptr) {
		e->addSnap(frontSnap);
		frontSnap->who->addSnap(new Snap(e, frontSnap->index == 0, 0));
	}
	if (tailSnap != nullptr) {
		e->addSnap(tailSnap);
		tailSnap->who->addSnap(new Snap(e, tailSnap->index == 0, e->getNum()-1));
	}
	return e;
}

void Cursor::reset()
{
	frontSnap = nullptr;
	tailSnap = nullptr;
	current_tool->reset();
}

void Cursor::useBezierTool()
{
	delete current_tool;
	this->current_tool = new BezierTool();
}

void Cursor::useLineTool()
{
	delete current_tool;
	this->current_tool = new LineTool();
}

void Cursor::usePointerTool()
{
	delete current_tool;
	PointerTool *e = new PointerTool();
	e->setStack(stack);
	current_tool = e;
}

void Cursor::setColor(int r, int g, int b)
{
	current_tool->setColor(r, g, b);
}

Element * Cursor::preview(int x, int y)
{
	snap = false;

	int snapPoint = -1;
	Element *snapElem = nullptr;

	for (int i = 0; i < stack->stackLocation; i++) {
		Element *e = stack->get(i);
		if (e != nullptr) {
			int temp = e->onMouseOver(x, y);
			if (temp != -1) {
				snapPoint = temp;
				snapElem = e;
			}
		}
	}

	if (snapPoint != -1) {
		x = snapElem->getPointX(snapPoint);
		y = snapElem->getPointY(snapPoint);

		snapX = x;
		snapY = y;
		snap = true;
		partner = snapElem;
		snapID = snapPoint;
	}

	if(current_tool != nullptr)
		return current_tool->preview(x,y);
	return nullptr;
}

Cursor::Cursor(DrawStack *stack)
{
	this->stack = stack;
}


Cursor::~Cursor()
{
}
