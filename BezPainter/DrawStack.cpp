#include "DrawStack.h"



DrawStack::DrawStack()
{
	stackLocation = 0;
	stackSize = 100;
	_stack = new Element*[100];
}


DrawStack::~DrawStack()
{
	for (int i = 0; i < stackLocation; i++) {
		delete _stack[i];
	}
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
	if (stackLocation < stackSize) {
		e->id = stackLocation;
		_stack[stackLocation++] = e;
		return true;
	}
	return false;
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

void DrawStack::hardReset()
{
	for (int i = 0; i < stackLocation; i++) {
		//delete _stack[i];
	}
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
	if(e != nullptr)
		e->id = i;
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
			f << s->who->id << ", " << s->front << ", " << s->index;
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

	reset();

	std::string line;
	std::ifstream f;

	std::string token;

	f.open("saved_data.bez");
	int ln = 0;
	while(getline(f, line)){
		std::stringstream ss(line);
		char ignore;
		float ig;
		int type;

		float points[20] = {};

		int i = 0;

		ss >> type >> ignore >> ignore;
		while (ss >> points[i * 2] >> ignore >> points[i * 2 + 1]) {
			i++;
			ss >> ignore;

			if (ignore == ']')
				break;
		}

		ss >> ignore;

		int z = 0;
		while (ss >> ig >> ignore >> ig >> ignore >> ig) {
			z++;
			ss >> ignore;

			if (ignore == ']')
				break;
		}

		ss >> ignore;

		int r;
		int g;
		int b;

		ss >> r >> ignore >> g >> ignore >> b;


		Element *e;

		switch (type) {
		case BEZIER:
			e = new BezierElement();
			for (int j = 0; j < i; j++) {
				e->addPoint(points[j * 2], points[j * 2 + 1]);
			}
			break;
		case LINE:
			e = new LineElement();
			for (int j = 0; j < i; j++) {
				e->addPoint(points[j * 2], points[j * 2 + 1]);
			}
			break;
		}
		e->setColor(r, g, b);
		e->id = ln;
		_stack[ln] = e;
		ln++;
	}

	stackLocation = ln;

	f.close();
	f.open("saved_data.bez");

	ln = 0;

	while (getline(f, line)) {
		line = line.substr(line.find_first_of("\]")+2);
		printf("%s\n", line.c_str());

		char ignore;

		std::stringstream ss(line);

		ss >> ignore;

		int snaps[60] = {};

		int z = 0;
		while (ss >> snaps[z*3] >> ignore >> snaps[z * 3+1] >> ignore >> snaps[z * 3+2]) {
			z++;
			ss >> ignore;

			if (ignore == ']')
				break;
		}

		Snap** rs = new Snap*[20];

		for (int i = 0; i < z; i++) {
			_stack[ln]->addSnap(new Snap(_stack[snaps[i * 3]], (bool)snaps[i * 3 + 1], snaps[i * 3 + 2]));
		}

		ln++;
	}
	f.close();

}
