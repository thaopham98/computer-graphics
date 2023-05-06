//////////////////////////////////////////////////////////////////////
// mouse.cpp
//
// This program illustrates interaction using the mouse.
//
// Interaction:
// Left mouse click to draw a square point, right mouse click to exit.
//
// Sumanta Guha.
//////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <cmath>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int width, height; // OpenGL window size.

#define MSEC_PER_FRAME 16.6 //60 frames per second => 1000/60

#define MOVE_LEFT 0
#define MOVE_UP 1
#define MOVE_RIGHT 2
#define MOVE_DOWN 3

int motionState = 0;
int obj_x = 250;
int obj_y = 250;

void drawObject(float x,float y,int size){
	glBegin(GL_POLYGON);
	glVertex3f(x-size, y-size, 0.0);
	glVertex3f(x+size, y-size, 0.0);
	glVertex3f(x+size, y+size, 0.0);
	glVertex3f(x-size, y+size, 0.0);
	glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	drawObject(obj_x,obj_y,50);

	glFlush();
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){

	if(motionState == MOVE_LEFT)
		obj_x = (obj_x - 5);
	else if(motionState == MOVE_RIGHT)
		obj_x = (obj_x + 5);
	else if(motionState == MOVE_UP)
		obj_y = (obj_y + 5);
	else
		obj_y = (obj_y - 5);

  glutPostRedisplay();
  glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
}

// Initialization routine.
void setup(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h){
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
	switch (key)
	{
	case ' ':
		motionState = (motionState + 1)%4;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

// Main routine.
int main(int argc, char **argv){

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Time Function Example");
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
