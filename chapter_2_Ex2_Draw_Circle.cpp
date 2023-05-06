///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <GL/freeglut.h>
#include <cmath>
#define PI 3.14

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Define Parameters of circle
	static float R = 40.0; // Radius of circle.
	static float X = 50.0; // X of center.
	static float Y = 50.0; // Y of center.
	static int numVertices = 100; // #vertices.

	glColor3f(0.0, 0.0, 0.0);
	float t = 0;
	//Empty circle
	 glBegin(GL_LINE_LOOP);
	 for (int i = 0; i < numVertices; i++)
	 {
	 	glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
	 	t += 2 * PI / numVertices;
	 }
	 glEnd();

	//Circle with
//	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//	glBegin(GL_TRIANGLE_FAN);
//	glVertex3f(X,Y,0); //center point
//	for (int i = 0; i < numVertices+1; i++)
//	{
//		glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
//		t += 2 * PI / numVertices;
//	}
//	glEnd();

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
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

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

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out squareEx.cpp
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("square.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
