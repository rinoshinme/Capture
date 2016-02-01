#if 1
#include <GL\glut.h>
#include <vector>
#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>

#include "../IncludeAll.h"

using namespace Capture;

// range of position values
double width = 800;
double height = 600;

SimpleSound sound;
std::vector<double> coef;
std::vector<double> source;
const int LEN = 1024;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	sound = WavRead("E:\\Projects\\Sparks Fly.wav", 0);
	double* data = sound.GetPtrData();
	source.resize(LEN);
	for (int i = 0; i < LEN; ++i)
		source[i] = data[i + 300000];

	MFCC mfcc(LEN);
	coef = mfcc.Calculate(source, 8000, 12);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// draw coef
	double barWidth = 50;
	double xStart = width / 8;
	double yStart = height / 4;
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	int size = coef.size();
	for (int i = 0; i < size; ++i)
	{
		glColor3f(1.0 * (i % 2), 1.0 * ((i+1) % 2), 0.0);
		glVertex2f(xStart + i * barWidth, yStart);
		glVertex2f(xStart + i * barWidth, yStart + coef[i] * 1);
		glVertex2f(xStart + (i+1) * barWidth, yStart + coef[i] * 1);
		glVertex2f(xStart + (i+1) * barWidth, yStart);
	}
	glEnd();

	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Testing MFCC");

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

#endif
