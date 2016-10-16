#include <stdlib.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

using namespace std;

void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	// background color: black
	glColor3f(1.0f, 1.0f, 1.0f);		// drawing color: white
	glLineWidth(5.0);					// a line is 5 pixels wide
	glMatrixMode(GL_PROJECTION);		// set matrix mode
	glLoadIdentity();					// load identity matrix
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);	// orthographic mapping

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glutSwapBuffers();

}

int main(int argc, char**argv)
{
	// Basic glut setup
	glutInit(&argc, argv);										// initialize toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// set display mode
	glutInitWindowSize(500, 500);								// set window size
	glutInitWindowPosition(100, 100);							// set window position on screen
	glutCreateWindow("HW5");									// open screen window

	myInit();	// additional inits

	// register callback functions
	glutDisplayFunc(display);

	glMatrixMode(GL_PROJECTION);

	glutMainLoop();


}