#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <GL/glut.h>

using namespace std;

// global variables for positioning camera based on mouse movement
GLfloat eyex, eyey, eyez;
GLfloat vAngle, hAngle;

// init callback
void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);	// background color: black
	glColor3f(0.0f, 0.0f, 0.0f);		// drawing color: white
	glLineWidth(2.0);					// a line is 5 pixels wide

	glMatrixMode(GL_PROJECTION);		// set matrix mode
	glLoadIdentity();					// load identity matrix
	glOrtho(-3.5, 3.5, -3.0, 4.0, -10.0, 10.0);	// orthographic mapping

	// set up ability to track object depths
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

}

// plotting function
GLfloat f(GLfloat x, GLfloat z) {
	return 2 * x*x + 2 * z*z - 1;
}

// calculates where camera should be positioned
void eyeAt(GLfloat r) {
	eyez = r * sin(vAngle) * cos(hAngle);
	eyex = r * sin(vAngle) * sin(hAngle);
	eyey = r * cos(vAngle);
}

// display callback
void display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear screen to bg color

	eyeAt(2.0);	// reposition camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);

	// establish range and increment for function
	GLfloat xstart = -1, xend = 1;
	GLfloat zstart = -1, zend = 1;
	GLfloat inc = 0.1;

	for (GLfloat x = xstart; x < xend; x = x + inc) {
		for (GLfloat z = zstart; z < zend; z = z + inc) {

			// draw solid representation of function
			glColor3f(0.0, 0.0, 1.0);
			glBegin(GL_QUADS);
				glVertex3f(x, f(x, z), z);
				glVertex3f(x + inc, f(x + inc, z), z);
				glVertex3f(x + inc, f(x + inc, z + inc), z + inc);
				glVertex3f(x, f(x, z + inc), z + inc);
			glEnd();

			// draw black wire mesh over top of solid representation
			glEnable(GL_POLYGON_OFFSET_FILL);
			glPolygonOffset(1.0, 1.0);
			glColor3f(0.0, 0.0, 0.0);

			glBegin(GL_LINES);
				glVertex3f(x, f(x, z), z);
				glVertex3f(x + inc, f(x + inc, z), z);

				glVertex3f(x + inc, f(x + inc, z), z);
				glVertex3f(x + inc, f(x + inc, z + inc), z + inc);

				glVertex3f(x + inc, f(x + inc, z + inc), z + inc);
				glVertex3f(x, f(x, z + inc), z + inc);
			glEnd();

			glDisable(GL_POLYGON_OFFSET_FILL);
			 
		}
	}

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

// reshape callback
void reshape(int w, int h) {

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (w <= h) {
		glOrtho(-3.5, 3.5, -3.0 * (GLfloat)h / (GLfloat)w, 4.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	}
	else {
		glOrtho(-3.5 * (GLfloat)w / (GLfloat)h, 3.5* (GLfloat)w / (GLfloat)h, -3.0, 4.0, -10.0, 10.0);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

// mouse movement callback
void mouse(int x, int y) {

	hAngle = (360.0 / glutGet(GLUT_WINDOW_WIDTH) * (x + 1)); // 360 degrees
	vAngle = (180.0 / glutGet(GLUT_WINDOW_HEIGHT) * (y + 1)); // 180 degrees
	hAngle = hAngle * 0.017453;
	vAngle = vAngle * 0.017453;

	glutPostRedisplay();
}

// main method
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
	glutMotionFunc(mouse);

	glMatrixMode(GL_PROJECTION);

	glutMainLoop();


}