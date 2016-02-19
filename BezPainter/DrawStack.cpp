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

void DrawStack::draw(graphics *g)
{
	for (int i = 0; i < stackLocation; i++) {
		if (_stack[i] != nullptr) {
			_stack[i]->draw(g);
		}
	}
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

void DrawStack::save()
{
	std::ofstream f;
	f.open("saved_data.bez");
	Element *e;
	Snap *s;
	for (int i = 0; i < stackLocation; i++) {
		e = get(i);
		int type = e->getType();
		f << type << ": [";
		for (int j = 0; j < e->getNum(); j++) {
			f << e->getPointX(j) << ", " << e->getPointY(j);
			if (j != e->getNum() - 1)
				f << ", ";
		}
		f << "] [";
		for (int j = 0; j < e->snapNum; j++) {
			s = e->snaps[j];
			f << "{" << s->who->id << ", " << s->front << ", " << s->index << "}";
			if (j != e->snapNum - 1)
				f << ", ";
		}
		f << "] [" << e->color[0] << ", " << e->color[1] << ", " << e->color[2] << "]";
		f << std::endl;
	}
	f.close();
}

void DrawStack::load()
{
	std::string line;
	std::ifstream f;

	std::string token;

	f.open("saved_data.bez");
	
	while(getline(f, line)){
		std::stringstream ss(line);
		char ignore;
		int type;

		float points[8] = {};

		ss >> type >> ignore >> ignore;
		for (int i = 0; i < 4; i++) {
			ss >> points[i * 2] >> ignore >> ignore >> points[i * 2 + 1];
			ss >> ignore;
		}

	}
}
