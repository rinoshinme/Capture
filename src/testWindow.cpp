#if 0
#include <GL\glut.h>
#include <iostream>
#include "source\window\RectangularWindow.h"
#include "source\window\GaussianWindow.h"
#include "source\window\HannWindow.h"
#include "source\window\HammingWindow.h"
using namespace Capture;

// range of position values
double width = 800;
double height = 600;

RectangularWindow rw;
GaussianWindow gw;
HannWindow hnw;
HammingWindow hmw;

const int LEN = 128;
void init()
{
	rw = RectangularWindow(LEN);
	gw = GaussianWindow(LEN, 0.3);
	hnw = HannWindow(LEN);
	hmw = HammingWindow(LEN);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// x axis
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(0.0, height/4);
	glVertex2f(width, height/4);
	glEnd();

	// rectangular window
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < LEN; ++i)
		glVertex2f(width/8 + (i*1.0/LEN) * width * 3/4, 0 + height / 4 + height / 2 * rw[i]);
	glEnd();

	// gaussian window
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < LEN; ++i)
		glVertex2f(width/8 + (i*1.0/LEN) * width * 3/4, 0 + height / 4 + height / 2 * gw[i]);
	glEnd();

	// hann window
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < LEN; ++i)
		glVertex2f(width/8 + (i*1.0/LEN) * width * 3/4, 0 + height / 4 + height / 2 * hnw[i]);
	glEnd();

	// hamming window
	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < LEN; ++i)
		glVertex2f(width/8 + (i*1.0/LEN) * width * 3/4, 0 + height / 4 + height / 2 * hmw[i]);
	glEnd();

	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Drawing window functions");

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}



#endif