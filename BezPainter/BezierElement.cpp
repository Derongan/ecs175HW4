#include "BezierElement.h"



BezierElement::BezierElement()
{
	num = 10;
	id = curid++;

	points = new float[20];
	show = new int[10];
}


BezierElement::~BezierElement()
{
}

void BezierElement::drawSelf(graphics *g)
{
	g->setColor(color[0], color[1], color[2]);
	g->bezier(this->points, this->num);
}

void BezierElement::setPoints(float * points, int num)
{
	for (int i = 0; i < num*2; i++) {
		this->points[i] = points[i];
	}
	this->num = num;
}

void BezierElement::onMouseDown(int x, int y)
{
	if (num >= 20)
		return;

	points[num * 2] = x;
	points[num * 2 + 1] = y;
	num++;
}

bool BezierElement::inside(float x, float y)
{
	float maxX, maxY, minX, minY;
	maxX = minX = points[0];
	minY = maxY = points[1];

	for (int i = 1; i < num; i++) {
		maxX = fmax(maxX, points[2 * i]);
		maxY = fmax(maxY, points[2 * i + 1]);
		minX = fmin(minX, points[2 * i]);
		minY = fmin(minY, points[2 * i + 1]);
	}

	return (x - 4 < maxX && x + 4 > minX && y - 4 < maxY && y + 4 > minY);
}

int BezierElement::getClickedControlPoint(float x, float y)
{
	for (int i = 0; i < num; i++) {
		int x1 = points[i * 2];
		int y1 = points[i * 2 + 1];

		if (x - 4 < x1 && x + 4 > x1 && y - 4 < y1 && y + 4 > y1)
			return i;
	}
	return -1;
}


void BezierElement::snap(Element * e, int index)
{
}

TYPE BezierElement::getType()
{
	return BEZIER;
}

void BezierElement::updateSnaps()
{
	Snap* snap;
	Element* e;
	int index;
	snappable = false;
	for (int i = 0; i < snapNum; i++) {
		snap = snaps[i];
		e = snap->who;
		index = snap->index;
		if (e->snappable && e->getType() == BEZIER) {
			if (snap->front) {
				e->points[index * 2] = points[0];
				e->points[index * 2 + 1] = points[1];

				int dx = points[0] - points[2];
				int dy = points[1] - points[3];

				if (index == 0) {
					e->points[2] = points[0] + dx;
					e->points[3] = points[1] + dy;
				}
				else {
					e->points[(e->getNum() - 2) * 2] = points[0] + dx;
					e->points[(e->getNum() - 2) * 2 + 1] = points[1] + dy;;
				}
			}
			else {
				int dx =  getPointX(num-1) - getPointX(num-2);
				int dy = getPointY(num - 1) - getPointY(num - 2);

				e->points[index * 2] = getPointX(num - 1);
				e->points[index * 2 + 1] = getPointY(num - 1);
				if (index == 0) {
					e->points[2] = getPointX(num - 1) + dx;
					e->points[3] = getPointY(num - 1) + dy;
				}
				else {
					e->points[(e->getNum() - 2) * 2] = getPointX(num - 1) + dx;
					e->points[(e->getNum() - 2) * 2 + 1] = getPointY(num - 1) + dy;
				}
			}

			e->updateSnaps();
		}
		else if (e->snappable) {
			if (snap->front) {
				e->points[index * 2] = points[0];
				e->points[index * 2 + 1] = points[1];
			}
			else {
				e->points[index * 2] = points[6];
				e->points[index * 2 + 1] = points[7];
			}
			e->updateSnaps();
		}
	}
	snappable = true;
}
