#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

// Function to draw a disc with center at (X, Y, Z), radius R, parallel to the xy-plane.
void drawDisc(float R, float X, float Y, float Z)
{
	float t;
	int i;

	glBegin(GL_LINE_STRIP);
	for (i = 0; i <= N; ++i)
	{
		t = 2 * PI * i / N;
		glVertex3f(X + cos(t) * R, Y + sin(t) * R, Z);
	}
	glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the buffers including the depth buffer.

	//Exercise 1: Draw two idendical circles one behind another
	glColor3f(1.0, 0.0, 0.0);
	drawDisc(2.0, -1.0, 0.0, -10); //closer red circle

	glColor3f(0.0, 1.0, 0.0);
	drawDisc(2.0, 1.0, 0.0, -10); //farther green circle

	//Exercise 2: Parallel Lines
	// glColor3f(0,0,0);
	// glBegin(GL_LINES);
	// 	glVertex3f(5,-5,-5); //Starts from bottom-right corner
	// 	glVertex3f(5,-5,-100); //goes until the far plane
	//
	// 	glVertex3f(-5,-5,-5); //Starts from bottom-left corner
	// 	glVertex3f(-5,-5,-100);//goes until the far plane
	// glEnd();

	//Exercise 3: Draw a wire cube
	//(Show at center (0,0,-10), then (3,-1,-10))
	// glColor3f(0,0,0);
	// glTranslatef(-2,-2,-10);
	// glutWireCube(5);

	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);
	//gluPerspective(90,w/h,5,100);

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
	glutCreateWindow("Perspective Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
