#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Cursor.h"
#include "graphics.h"
#include "DrawStack.h"
#include "PointElement.h"
#include "LineElement.h"

void display();
void click(int,int,int,int);
void createMenu();
void callbackMenu(int id);

const int WIDTH = 800;
const int HEIGHT = 600;


Cursor *c;
graphics *g;
DrawStack *s;
DrawStack *ts;

float last[2] = {0};
bool l = false;

int main(int argc, char *argv[])
{
	//allocate new pixel buffer, need initialization!!
	//Setup our cursor
	c = new Cursor();
	c->useBezierTool();

	//Setup drawing stack
	s = new DrawStack();
	ts = new DrawStack();

	g = new graphics(WIDTH, HEIGHT);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set window size to 200*200
	glutInitWindowSize(WIDTH, HEIGHT);
	//set window position
	glutInitWindowPosition(100, 100);

	//create and set main window title
	int MainWindow = glutCreateWindow("Hello Graphics!!");
	glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
							  //sets display function
	glutDisplayFunc(display);
	glutMouseFunc(click);
	createMenu();

	glutMainLoop();//main display loop, will display until terminate
	return 0;
}

void createMenu() {
	glutCreateMenu(callbackMenu);
	glutAddMenuEntry("Start", 0);
	glutAddMenuEntry("Finish", 1);
	glutAddMenuEntry("------", -1);
	glutAddMenuEntry("Point", 2);
	glutAddMenuEntry("Line", 3);
	glutAddMenuEntry("Curve", 4);
	glutAddMenuEntry("------", -1);
	glutAddMenuEntry("continueCurve", 5);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void callbackMenu(int id) {
	switch (id) {
	case 1:
		c->setColor(1, 0, 0);
		s->push(c->finish());
		c->reset();
		ts->reset();
		l = false;
		break;
	case 3:
		c->reset();
		c->useLineTool();
		ts->reset();
		break;
	case 4:
		c->reset();
		c->useBezierTool();
		ts->reset();
		break;
	case 5:
		c->setColor(1, 0, 0);

		Element *e = c->finish();

		s->push(e);
		c->reset();
		ts->reset();
		l = false;

		break;
	}
	glutPostRedisplay();
}

void click(int button, int state, int x, int y) {
	y = HEIGHT - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		c->addPoint(x, y);
		Element* e = new PointElement(x, y);
		e->setColor(0, 1, 0);
		if (l) {
			Element* e = new LineElement(x, y, last[0], last[1]);
			e->setColor(.8, 0, .8);
			ts->push(e);
		}
		ts->push(e);
		last[0] = x;
		last[1] = y;
		l = true;
		printf("Starting drawing drawing\n");
	}
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	g->clearBuffer();
	g->setColor(1, 0, 0);

	s->draw(g);
	ts->draw(g);

	g->setColor(0, 1, 0);

	//draws pixel on screen, width and height must match pixel buffer dimension
	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_FLOAT, g->getCurrentBuffer());

	//window refresh
	glFlush();
}