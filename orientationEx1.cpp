///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <GL/freeglut.h>

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// -- Enable Face Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// -- Change the default face orientation
	//glFrontFace(GL_CCW);

	// -- Draw a polygon with specified vertices.
	glPolygonMode(GL_FRONT, GL_FILL);
  glPolygonMode(GL_BACK, GL_LINE);

	glBegin(GL_TRIANGLES);
   // Face (Red) => CW
	glColor3f(1,0,0);
	glVertex3f(20.0, 80.0, 0.0);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(50.0, 80.0, 0.0);

	// Face (Green) => CCW
	glColor3f(0,1,0);
	glVertex3f(50.0, 80.0, 0.0);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(50.0, 20.0, 0.0);

	// Face (Blue) => CW
	glColor3f(0,0,1);
	glVertex3f(50.0, 20.0, 0.0);
	glVertex3f(50.0, 80.0, 0.0);
	glVertex3f(80.0, 80.0, 0.0);

	// Face (Yellow) => CCW
	glColor3f(1,1,0);
	glVertex3f(80.0, 80.0, 0.0);
	glVertex3f(50.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);

	glEnd();

	// -- consistently oriented faces
	// glColor3f(0,0,0);
	// glBegin(GL_TRIANGLE_STRIP);
	//   glVertex3f(20.0, 80.0, 0.0);
	//   glVertex3f(20.0, 20.0, 0.0);
	//   glVertex3f(50.0, 80.0, 0.0);
	//   glVertex3f(50.0, 20.0, 0.0);
	//   glVertex3f(80.0, 80.0, 0.0);
	//   glVertex3f(80.0, 20.0, 0.0);
	// glEnd();

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
