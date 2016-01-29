#if 0
/*
 * Draw sound waveform using opengl
 */
#include <GL\glut.h>
#include <string>
#include "sound\simple_wav.h"

using namespace Capture;

static SimpleSound s;
const int LEN = 40000;

// range of position values
double width = 8000;
double height = 6000;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, width, 0.0, height);

	std::string infile("E:\\Projects\\Sparks Fly.wav");
	s = WavRead(infile, 0);
}

void display()
{
	double* data = s.GetPtrData();
	glColor3f(0.0, 1.0, 0.0);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < LEN; ++i)
		glVertex2f(i * (width / LEN), data[i + 300000] * (height/2) + height/2);
	glEnd();

	glFlush();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Drawing waveform");

	init();
	glutDisplayFunc(display);
	glutMainLoop();
}

#endif
