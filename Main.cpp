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
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);	// orthographic mapping

}

void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen to bg color
	glMatrixMode(GL_MODELVIEW);

	// draw a blue sphere
	 glColor3f(0.0, 0.0, 1.0);
	 glutWireSphere(2.0, 10, 10);

	// draw a yellow plane	
	glBegin(GL_QUADS);
		glColor3f(1.0, 1.0, 0.0);

		glVertex3f(2.0, 0.0, 2.0);
		glVertex3f(-2.0, 0.0, 2.0);
		glVertex3f(-2.0, 0.0, -2.0);
		glVertex3f(2.0, 0.0, -2.0);
	glEnd();

	glutSwapBuffers();	// draw to screen

}

void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-10.0, 10.0, -10.0 * (GLfloat)h / (GLfloat)w, 10.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-10.0 * (GLfloat)w / (GLfloat)h, 10.0* (GLfloat)w / (GLfloat)h, -10.0, 10.0, -10.0, 10.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
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
	glutReshapeFunc(reshape);

	glMatrixMode(GL_PROJECTION);

	glutMainLoop();


}