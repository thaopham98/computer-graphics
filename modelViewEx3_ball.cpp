#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define MSEC_PER_FRAME 10

float t = 0;//time

//x velocity = 0.7
float xPos(float t){return 0.7*t;}

//y velocity = 4.0, gravity = 0.2
float yPos(float t){return 4.0*t - (0.2 / 2.0)*t*t;}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(xPos(t), yPos(t), 0.0);
	glTranslatef(-15.0, -25.0, -25.0); //Initial Position

	glColor3f(1,0,0); glutSolidSphere(2,10,10); // Ball Object.

	glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case ' ':
			t = 0;
			break;
		default:
			break;
	}
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){
	t+=0.5;
  glutPostRedisplay();
  glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
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
	//gluPerspective(90,w/h,5,100);
	glOrtho(-25,25,-25,25,5,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Modelview Transformation Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);


	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
