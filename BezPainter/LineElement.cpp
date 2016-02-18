#include "LineElement.h"



LineElement::LineElement()
{
}

LineElement::LineElement(int x0, int y0, int x1, int y1)
{
	points[0] = x0;
	points[1] = y0;
	points[2] = x1;
	points[3] = y1;
}


LineElement::~LineElement()
{
}

void LineElement::draw(graphics * g)
{
	g->setColor(color[0], color[1], color[2]);
	g->bLine(points[0], points[1], points[2], points[3]);
}

void LineElement::drawControlPoints(graphics * g)
{
	for (int i = 0; i < 2; i++) {
		g->setColor(0, 1, 0);
		for (int j = 0; j < 7; j++) {
			g->setPixel(points[i * 2] + j - 3, points[i * 2 + 1] + 3);
			g->setPixel(points[i * 2] + j - 3, points[i * 2 + 1] - 3);
			g->setPixel(points[i * 2] - 3, points[i * 2 + 1] + j - 3);
			g->setPixel(points[i * 2] + 3, points[i * 2 + 1] + j - 3);
		}
	}
}
