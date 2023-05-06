#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int width, height; // OpenGL window size.

#define MSEC_PER_FRAME 16.6 //60 frames per second => 1000/60

bool pauseMotion = false;

int obj_x = 250;
int obj_y = 250;

int rot = 0;
int totalDegress = 0;

void drawObject(int size) {
	glBegin(GL_POLYGON);
	glVertex3f(-size, -size, 0.0);
	glVertex3f(+size, -size, 0.0);
	glVertex3f(+size, +size, 0.0);
	glVertex3f(-size, +size, 0.0);
	glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(obj_x, obj_y, 0);
	glRotatef(rot, 0, 0, 1);
	drawObject(50);

	glFlush();
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value) {

	if (!pauseMotion) {
		//obj_x += 1;
		//obj_y -= 1;
		if(rot < totalDegress)
			rot = (rot + 1) % 360;
	}

	glutPostRedisplay();
	glutTimerFunc(MSEC_PER_FRAME, timerFunc, value);
}

// Initialization routine.
void setup(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

	// Pass the size of the OpenGL window to globals.
	width = w; height = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	int randNum;
	switch (key)
	{
	case ' ':
		if (pauseMotion) pauseMotion = false;
		else pauseMotion = true;

		//generate random number here
		//totalDegrees = x*45;
		break;
	case 'r':
		rot = 0;
		randNum = rand() % 10;
		totalDegress = randNum * 45;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char** argv) {

	srand(time(0));

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Modelview Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	// Register the timer callback function.
	glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
