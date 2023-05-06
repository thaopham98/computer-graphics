#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define MSEC_PER_FRAME 10

float posX = 0, posY = 0;
float rot = 0;

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

void drawTriangle(float side){
	glBegin(GL_TRIANGLES);
		glVertex3f(-side/2,-side/2,0);
		glVertex3f(side/2,-side/2,0);
		glVertex3f(side/2,side/2,0);
	glEnd();
}
void drawSquare(float side){
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-side/2,-side/2,0);
		glVertex3f(-side/2,side/2,0);
		glVertex3f(side/2,side/2,0);
		glVertex3f(side/2,-side/2,0);
	glEnd();
}

void drawHome(float side){
	glTranslatef(0,side,0);
	glRotatef(135,0,0,1);
	glColor3f(1,0,0);drawTriangle(side);

	glLoadIdentity();
	glTranslatef(0,side/2,0);
	glColor3f(0,0,1);drawSquare(side);
}

void drawHome2(float side){
	glPushMatrix();
	glTranslatef(0,side,0);
	glRotatef(135,0,0,1);
	glColor3f(0.5,0,0);drawTriangle(side);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,side/2,0);
	glColor3f(0,0,0.5);drawSquare(side);
	glPopMatrix();
}

void drawScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	drawAxis(20);

	glTranslatef(posX,posY,0);
	glRotatef(rot,0,0,1);
	drawHome(8);

	//------------------------------------------------
	glDisable(GL_DEPTH_TEST);
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
		case 'a':
			posX--;
			break;
		case 'd':
			posX++;
			break;
		case 's':
			posY--;
			break;
		case 'w':
			posY++;
			break;
		case 'r':
			rot+=5;
			break;
		default:
			break;
	}
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){
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
int main(int argc, char **argv){
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
