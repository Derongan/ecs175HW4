#include "DrawStack.h"



DrawStack::DrawStack()
{
	stackLocation = stackSize = 0;
	_stack = new Element*[100];
}


DrawStack::~DrawStack()
{
	delete[] _stack;
}

void DrawStack::draw(graphics *g, bool w)
{
	for (int i = 0; i < stackLocation; i++) {
		if (_stack[i] != nullptr) {
			_stack[i]->draw(g);
			if (w)
				_stack[i]->drawControlPoints(g);
		}
	}
}

void DrawStack::draw(graphics * g)
{
	draw(g, false);
}

bool DrawStack::push(Element *e)
{
	_stack[stackLocation++] = e;
	return true;
}

bool DrawStack::pop()
{
	if (stackLocation <= 0)
		return false;
	else {
		stackLocation--;
		return true;
	}
}

void DrawStack::reset()
{
	stackLocation = 0;
}

Element* DrawStack::get(int i)
{
	if (i > stackLocation)
		return nullptr;
	return _stack[i];
}

void DrawStack::set(int i, Element * e)
{
	if (i > stackLocation)
		return;
	_stack[i] = e;
}
