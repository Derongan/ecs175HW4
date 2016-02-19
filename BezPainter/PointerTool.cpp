#include "PointerTool.h"

PointerTool::PointerTool()
{
}

PointerTool::~PointerTool()
{
	replaceElement();
}

bool PointerTool::onMouseDown(float x, float y)
{
	Element *e;
	down = true;
	if (this->e != nullptr) {
		int i = this->e->getClickedControlPoint(x, y);
		lx = x;
		ly = y;
		if (i != -1) {
			movingPt = true;
			pind = i;
			this->e->setControlPoint(i, 2);
			return true;
		}
		if (this->e->inside(x, y)) {
			return true;
		}
	}
	for (int i = 0; i < stack->stackLocation; i++) {
		e = stack->get(i);
		if (e != nullptr) {
			if (e->inside(x, y)) {
				replaceElement();
				stack->set(i, nullptr);
				this->e = e;
				e->setControlPoint(-1, 1);
				this->index = i;
				return true;
			}
		}
	}
	replaceElement();
	return true;
}

void PointerTool::onMouseUp(float x, float y)
{
	if(this->e != nullptr)
		this->e->setControlPoint(-1, 1);
	down = false;
	movingPt = false;
}

Element * PointerTool::finish()
{
	return nullptr;
}

void PointerTool::reset()
{
}

void PointerTool::setColor(float r, float g, float b)
{
}

Element * PointerTool::preview(int x, int y)
{
	if(e == nullptr)
		return nullptr;
	else {
		if (down && !movingPt) {
			e->translate(x - lx, y - ly, -1);
			lx = x;
			ly = y;
		}
		else if( down && movingPt){
			e->translate(x - lx, y - ly, pind);
			lx = x;
			ly = y;
		}
		return e;
	}
}

void PointerTool::replaceElement()
{
	if (index != -1 && e != nullptr) {
		stack->set(index, e);
		e->setControlPoint(-1, 0);
		index = -1;
		e = nullptr;
	}
}
