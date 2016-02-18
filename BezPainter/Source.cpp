#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include "Cursor.h"
#include "graphics.h"
#include "DrawStack.h"
#include "PointElement.h"
#include "LineElement.h"
#include "Painter.h"

void display();
void click(int,int,int,int);
void move(int, int);
void createMenu();
void callbackMenu(int id);

const int WIDTH = 800;
const int HEIGHT = 600;


Cursor *c;
graphics *g;
DrawStack *s;
DrawStack *ts;

Painter *p;

float last[2] = {0};
bool l = false;

int main(int argc, char *argv[])
{
	//allocate new pixel buffer, need initialization!!

	g = new graphics(WIDTH, HEIGHT);

	p = new Painter(g);

	c = p->getCursor();

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
	glutPassiveMotionFunc(move);
	createMenu();

	glutMainLoop();//main display loop, will display until terminate
	return 0;
}

void move(int x, int y) {
	p->onMove(x, HEIGHT - y);
	glutPostRedisplay();
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
		c->reset();
		break;
	case 3:
		c->reset();
		c->useLineTool();
		break;
	case 4:
		c->reset();
		c->useBezierTool();
		break;
	case 5:
		c->reset();
		break;
	}
	glutPostRedisplay();
}

void click(int button, int state, int x, int y) {
	y = HEIGHT - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p->onClick(button, state, x, y);
	}
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	g->clearBuffer();

	p->draw();
	//draws pixel on screen, width and height must match pixel buffer dimension
	glDrawPixels(WIDTH, HEIGHT, GL_RGB, GL_FLOAT, g->getCurrentBuffer());

	//window refresh
	glFlush();
}