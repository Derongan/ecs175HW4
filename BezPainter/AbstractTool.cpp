#include "AbstractTool.h"



AbstractTool::AbstractTool()
{
	setColor(0, 1, 0);
}


AbstractTool::~AbstractTool()
{
}

void AbstractTool::setColor(float r, float g, float b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

Element * AbstractTool::preview(int x, int y)
{
	return nullptr;
}

void AbstractTool::onMouseUp(float x, float y)
{
}
