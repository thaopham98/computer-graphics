#include <GL/freeglut.h>
#include <cmath>
int objx = 50;
int objy = 50;
int n = 20;
void drawStar(float x, float y, int size){
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0);
    glVertex3f(x, y+size, 0.0);
    glVertex3f(x+size/3, y+size/3, 0.0);
    glVertex3f(x+size, y, 0.0);
    glVertex3f(x+size/3, y-size/3, 0.0);
    glVertex3f(x, y-size, 0.0);
    glVertex3f(x-size/3, y-size/3, 0.0);
    glVertex3f(x-size, y, 0.0);
    glVertex3f(x-size/3, y+size/3, 0.0);
    glVertex3f(x, y+size, 0.0);
    glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw a polygon with specified vertices.
	glColor3f(0,0,0);
    drawStar(objx, objy, n);

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

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out 4pointedStar.cpp
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("4pointedStar.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
