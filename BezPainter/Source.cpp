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
void callbackSub(int id);

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
	glutMotionFunc(move);
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
	int submenu = glutCreateMenu(callbackSub);
	glutAddMenuEntry("Red", 0);
	glutAddMenuEntry("Green", 1);
	glutAddMenuEntry("Blue", 2);

	int menu = glutCreateMenu(callbackMenu);
	glutAddMenuEntry("Finish Curve", 1);
	glutAddMenuEntry("Point", 2);
	glutAddMenuEntry("Line", 3);
	glutAddMenuEntry("Curve", 4);
	glutAddMenuEntry("Select", 5);
	glutAddMenuEntry("-----", -1);
	glutAddMenuEntry("Save", 10);
	glutAddMenuEntry("Load", 11);
	glutAddMenuEntry("Reset", 12);
	glutAddSubMenu("Color", submenu);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void callbackSub(int id) {
	switch (id) {
	case 0:
		c->setColor(1, 0, 0);
		break;
	case 1:
		c->setColor(0, 1, 0);
		break;
	case 2:
		c->setColor(0, 0, 1);
		break;
	}
}

void callbackMenu(int id) {
	switch (id) {
	case 1:
		p->addElement(c->finish());
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
		c->usePointerTool();
		break;
	case 10:
		c->reset();
		c->usePointerTool();
		p->save();
		break;
	case 11:		
		c->reset();
		c->usePointerTool();
		p->load();
		break;
	case 12:
		p->clear();
		c->reset();
		c->usePointerTool();
		break;
	}
	glutPostRedisplay();
}

void click(int button, int state, int x, int y) {
	y = HEIGHT - y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		p->onMouseDown(button, state, x, y);
		glutPostRedisplay();
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		p->onMouseUp(button, state, x, y);
		glutPostRedisplay();
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