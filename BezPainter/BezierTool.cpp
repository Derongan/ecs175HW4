#include "BezierTool.h"



BezierTool::BezierTool()
{
}

BezierTool::~BezierTool()
{
}

bool BezierTool::onMouseDown(float x, float y)
{
	this->points[this->pointNumber*2] = x;
	this->points[this->pointNumber*2 + 1] = y;
	this->pointNumber++;
	if (this->pointNumber >= MAXPOINTS)
		return false;
	return true;
}

Element* BezierTool::finish()
{
	BezierElement *e = new BezierElement();
	e->setPoints(points, pointNumber);
	e->setColor(color[0], color[1], color[2]);
	e->setControlPoint(-1, 0);
	return e;
}

void BezierTool::reset()
{
	this->pointNumber = 0;
}

Element * BezierTool::preview(int x, int y)
{
	BezierElement *e = new BezierElement();
	e->setPoints(points, pointNumber);
	e->onMouseDown(x, y);
	e->setColor(color[0], color[1], color[2]);
	e->setControlPoint(-1, 1);
	return e;
}

int BezierTool::snap(Element * e, int index)
{
	if (pointNumber == 0 && e->getType() == BEZIER) {
		int num = e->getNum();

		if (index == 0 || index == num - 1) {
			this->points[this->pointNumber * 2] = e->getPointX(index);
			this->points[this->pointNumber * 2 + 1] = e->getPointY(index);
			pointNumber++;
			if (index == 0) {
				int dx = e->getPointX(0) - e->getPointX(1);
				int dy = e->getPointY(0) - e->getPointY(1);
				this->points[this->pointNumber * 2] = e->getPointX(0) + dx;
				this->points[this->pointNumber * 2 + 1] = e->getPointY(0) + dy;
			}
			else if (index == num - 1) {
				int dx = e->getPointX(index) - e->getPointX(index - 1);
				int dy = e->getPointY(index) - e->getPointY(index - 1);
				this->points[this->pointNumber * 2] = e->getPointX(index) + dx;
				this->points[this->pointNumber * 2 + 1] = e->getPointY(index) + dy;
	
			}
			pointNumber++;
			return 1;
		}
	}

	else if (pointNumber == MAXPOINTS-1 && e->getType() == BEZIER) {
		int num = e->getNum();

		if (index == 0 || index == num - 1) {
			if (index == 0) {
				int dx = e->getPointX(0) - e->getPointX(1);
				int dy = e->getPointY(0) - e->getPointY(1);
				this->points[this->pointNumber * 2 - 2] = e->getPointX(0) + dx;
				this->points[this->pointNumber * 2 + 1 - 2] = e->getPointY(0) + dy;
			}
			else if (index == num - 1) {
				int dx = e->getPointX(index) - e->getPointX(index - 1);
				int dy = e->getPointY(index) - e->getPointY(index - 1);
				this->points[this->pointNumber * 2 - 2] = e->getPointX(index) + dx;
				this->points[this->pointNumber * 2 + 1 - 2] = e->getPointY(index) + dy;

			}
			return 2;
		}
	}
	return -1;
}
