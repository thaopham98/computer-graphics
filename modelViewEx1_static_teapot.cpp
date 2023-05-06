#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//------------------------------------------------
	/*Clear Transformations in Modelview matrix M = I*/
	glLoadIdentity();

	/*Create a translation matrix and a rotation matrix*/
	glTranslatef(0,0,-20); 	//Create matrix M1
	glRotatef(20,0,0,1);		//Create matrix M2
	glScalef(0.5,0.5,0.5);	//Create matrix M3
	//here M = M1 * M2 * M3;

	//Create a red teapot object "O1"
	glColor3f(1,0,0); glutWireTeapot(5.0);

	/* NOTE:
		O1 will be scaled down by 0.5, then rotated 20 degrees around
  	z dimension, then translated -30 units in z such as:

		O1' = M * O1

	 	Note that O1 is first multiplied with M3, then M2, then M1. This means
		scale is applied first. Then rotation, then translation.

		The order of transformations may return different final position.
	*/

	//------------------------------------------------
	/*We clear all existing transformations M = I*/
	glLoadIdentity();

	/*Create a translation matrix*/
	glTranslatef(0,0,-20); 		//Create matrix M4
	//Here M = M4

	/*Create a green teapot object "O2"*/
	glColor3f(0,1,0); glutWireTeapot(5.0);
	//O2' = M * O2

	//------------------------------------------------
	/*Here we are adding a rotation matrix to the previous transformations
	So currently, translation and rotation matrices are active.
	We did not clear it for the new object*/
	glRotatef(45,0,0,1); //Create matrix M5
	//Here M = M4 * M5 (including M3)

	/*Create a Blue square object "O3"*/
	glColor3f(0,0,1);
	glBegin(GL_LINE_LOOP);
	glVertex3f(-10.0, -10.0, 0.0);
	glVertex3f(10.0, -10.0, 0.0);
	glVertex3f(10.0, 10.0, 0.0);
	glVertex3f(-10.0, 10.0, 0.0);
	glEnd();

	/*
		O3 will be first rotated 45 degrees around z axis
		then it will be translated 20 units.

		O3' = M * O3
	*/

	glDisable(GL_DEPTH_TEST);
	glFlush();
}

// Initialization routine.
void setup(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,w/h,5,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Modelview Transformation Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
