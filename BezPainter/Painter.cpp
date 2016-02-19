#include "Painter.h"



Painter::Painter(graphics *g)
{
	mainStack = new DrawStack();
	tempStack = new DrawStack();
	cursor = new Cursor(mainStack);
	this->g = g;

	cursor->usePointerTool();
}


Painter::~Painter()
{
}

void Painter::draw()
{
	tempStack->draw(g, true);
	mainStack->draw(g);
}

void Painter::onMouseDown(int button, int state, int x, int y)
{
	if (!cursor->onMouseDown(x, y)) {
		Element *e = cursor->finish();
		cursor->reset();

		e->setColor(1, 0, 0);
		mainStack->push(e);
	}
}

void Painter::onMouseUp(int button, int state, int x, int y)
{
	cursor->onMouseUp(x, y);
}

void Painter::onMove(int x, int y)
{
	this->x = x;
	this->y = y;
	Element *e = cursor->preview(x, y);
	if (e != nullptr) {
		tempStack->pop();
		tempStack->push(e);
	}
	else {
		tempStack->reset();
	}
}

Cursor * Painter::getCursor()
{
	return cursor;
}
