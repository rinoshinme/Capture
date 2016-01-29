#if 0
#include <GL\glut.h>
#include "transform\OouraFFT.h"
#include "functions.h"
#include <vector>
#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace Capture;

// range of position values
double width = 800;
double height = 600;

const int LEN = 4096;

std::vector<double> input;
std::vector<Complex> output;

void init()
{
	input.resize(LEN);
	for (int i = 0; i < LEN; ++i)
	{
		input[i] = 2 * (RandomDouble() - 0.5);
		//input[i] = sin(i * M_PI / 30);
	}
	OouraFFT fft(LEN);
	output = fft.FFT(input);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);
	glPointSize(2.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < LEN; ++i)
		glVertex2f(width/8 + width*3/4 * i / LEN, height * 3 / 4 +  1 * output[i].real());
	glEnd();
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < LEN; ++i)
		glVertex2f(width/8 + width*3/4 * i / LEN, height / 4 +  50 * input[i]);
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
