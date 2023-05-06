#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define MSEC_PER_FRAME 10

float rotZ = 0;
float posY = 0;

bool pauseMotion = false;

void writeBitmapString(void *font, char *string){
	for (char* c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void drawAxis(float size){
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex3f(-size,0,0);
		glVertex3f(size,0,0);
	glEnd();

	glRasterPos3f(size, 0, 0.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+X");

	glColor3f(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,-size,0);
		glVertex3f(0,size,0);
	glEnd();

	glRasterPos3f(0, size, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Y");

	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,-size);
		glVertex3f(0,0,size);
	glEnd();

	glRasterPos3f(0, 0, size);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Z");
}

// Drawing routine.
void drawScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	drawAxis(20);

	//Box rotates around itself at the origin
	glLoadIdentity();
	glRotatef(rotZ,0,0,1);
	glColor3f(1,0,0); glutSolidCube(5);
	//
	 //Box rotates around itself at (15,15,-10) not origin
	 glLoadIdentity();
	 glTranslatef(15,15,-10);
	 glRotatef(rotZ,0,0,1);
	 glColor3f(1,0,1); glutSolidCube(5); // pink  square
	//
	 //Box rotates around origin after moving to (10,10,-10)
	 glLoadIdentity();
	 glRotatef(rotZ,0,0,1);
	 glTranslatef(10,10,-10);
	 glColor3f(0,0,1); glutSolidCube(5);
//
//	 //Box rotates around the origin at(5,5,-10) but keeps its orientation
	 glLoadIdentity();
	 glRotatef(rotZ,0,0,1);
	 glTranslatef(5,5,-10);
	 glRotatef(-rotZ,0,0,1);
	 glColor3f(0,1,0); glutSolidCube(5);

	//------------------------------------------------
	glDisable(GL_DEPTH_TEST);
	glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case ' ':
			if(pauseMotion) pauseMotion = false;
			else pauseMotion = true;
			break;
		default:
			break;
	}
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){
	if(!pauseMotion){
		rotZ += 1;
		//posY += 0.25;
	}

	if(rotZ > 360) rotZ = 0; /* Keep rotating non stop */
	//if(posY > 25) posY = -25;

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
	//gluPerspective(90,w/h,5,100);
	glOrtho(-25,25,-25,25,-5,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

	glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
