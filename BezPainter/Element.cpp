#include "Element.h"

Element::Element()
{
	snaps = new Snap*[20];
	setColor(0, 0, 1);
}


Element::~Element()
{
	printf("Deleting Element\n");
	delete[] points;
	delete[] show;
}

void Element::draw(graphics * g)
{
	drawSelf(g);
	drawControlPoints(g);
}

void Element::setColor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void Element::onMouseDown(int x, int y)
{
}

int Element::onMouseOver(int x, int y)
{
	int ret = -1;
	setControlPoint(-1, 0);
	if (inside(x, y)) {
		int i = getClickedControlPoint(x, y);

		if (i != -1) {
			setControlPoint(i, 2);
			ret = i;
		}
	}
	return ret;
}

bool Element::inside(float x, float y)
{
	return false;
}

void Element::drawControlPoints(graphics * g)
{
	for (int i = 0; i < num; i++) {
		int x = points[i * 2];
		int y = points[i * 2 + 1];
		switch (show[i]) {
		case 1:
			for (int j = 0; j < 9; j++) {
				g->setPixel(x + 4, y + j - 4);
				g->setPixel(x - 4, y + j - 4);
				g->setPixel(x + j - 4, y + 4);
				g->setPixel(x + j - 4, y - 4);
			}
			break;
		case 2:
			for (int j = 0; j < 9; j++) {
				for (int k = 0; k < 9; k++) {
					g->setPixel(x + k - 4, y + j - 4);
				}
			}
			break;
		}
	}
}

int Element::getClickedControlPoint(float x, float y)
{
	return -1;
}

float Element::getPointX(int index)
{
	return points[index * 2];
}

float Element::getPointY(int index)
{
	return points[index * 2 + 1];
}

void Element::setControlPoint(int index, int style)
{
	if (index == -1) {
		for (int i = 0; i < num; i++) {
			show[i] = style;
		}
	}
	else if (index < num) {
		show[index] = style;
	}
}

void Element::translate(float x, float y, int who)
{
	if (who == -1)
		for (int i = 0; i < num; i++) {
			points[i * 2] += x;
			points[i * 2 + 1] += y;
		}
	else {
		points[who * 2] += x;
		points[who * 2 + 1] += y;
	}
	updateSnaps();
}

TYPE Element::getType()
{
	return ELEMENT;
}

int Element::getNum()
{
	return num;
}

void Element::addSnap(Element* e, bool front, int index)
{
	snaps[snapNum++] = new Snap(e, front, index);
}

void Element::addSnap(Snap * snap)
{
	snaps[snapNum++] = snap;
}

void Element::addPoint(float x, float y)
{
	this->points[num * 2] = x;
	this->points[num * 2 + 1] = y;
	num++;
}

void Element::updateSnaps()
{
}
