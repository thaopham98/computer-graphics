///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <GL/freeglut.h>

void drawAxis(float size) {
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(-size, 0, 0);
	glVertex3f(size, 0, 0);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, -size, 0);
	glVertex3f(0, size, 0);
	glEnd();

	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, -size);
	glVertex3f(0, 0, size);
	glEnd();
}

void drawObject() {
	glColor3f(0, 0, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (int y = 0; y < 8; y+=2) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < 10; x+=2) {
			glVertex3f(x, y, 0);
			glVertex3f(x, y + 2, 0);
		}
		glEnd();
	}

	for (int z = 0; z < 8; z += 2) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int x = 0; x < 10; x += 2) {
			glVertex3f(x, 0, z);
			glVertex3f(x, 0, z+2);
		}
		glEnd();
	}

	glBegin(GL_POLYGON);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 8);
		glVertex3f(0, 8, 8);
		glVertex3f(0, 8, 0);
	glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(20, 20, 20, 0, 0, 0, 0, 1, 0);
	
	drawAxis(40);
	drawObject();

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
	//glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
	gluPerspective(90, 1, 0, 100);

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

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out SampleCodecpp.cpp
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
