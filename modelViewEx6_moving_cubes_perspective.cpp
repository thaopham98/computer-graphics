#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define MSEC_PER_FRAME 10

int rotZ = 0;
bool pauseMotion = false;

float xCam = 10, yCam = 10, zCam = 20;

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
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glLoadIdentity();
	gluLookAt(xCam,yCam,zCam,0,0,-10,0,1,0);
	drawAxis(20);

	//------------------------------------------------
	glPushMatrix();
		glRotatef(rotZ,0,0,1);
		glColor3f(0,0,0); glutWireCube(5);
		glColor3f(1,0,0); glutSolidCube(5);
	glPopMatrix();

	//------------------------------------------------
	glPushMatrix();
		glTranslatef(15,15,0);
		glRotatef(rotZ,0,0,1);
		glColor3f(0,0,0); glutWireCube(5);
		glColor3f(1,0,1); glutSolidCube(5);
	glPopMatrix();

	//------------------------------------------------
	glPushMatrix();
		glRotatef(rotZ,0,0,1);
		glTranslatef(10,10,0);
		glColor3f(0,0,0); glutWireCube(5);
		glColor3f(0,0,1); glutSolidCube(5);
	glPopMatrix();

	//------------------------------------------------
	glPushMatrix();
		glRotatef(rotZ,0,0,1);
		glTranslatef(5,5,0);
		glRotatef(-rotZ,0,0,1);
		glColor3f(0,0,0); glutWireCube(5);
		glColor3f(0,1,1); glutSolidCube(5);
	glPopMatrix();
	//------------------------------------------------
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();
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
	
    gluPerspective(90,w/h,5,100);
	
    //glOrtho(-25,25,-25,25,-5,100);

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
		case ' ':
			if(pauseMotion) pauseMotion = false;
			else pauseMotion = true;
			break;
		case 'a':
			xCam-=0.5;
			break;
		case 'd':
			xCam+=0.5;
			break;
		case 'w':
			yCam+=0.5;
			break;
		case 's':
			yCam-=0.5;
			break;
		case 'u':
			zCam-=0.5;
			break;
		case 'j':
			zCam+=0.5;
			break;
		default:
			break;
	}
	//std::cout << x << " " << y << " " << z << std::endl;

}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){
	if(!pauseMotion)
		rotZ = (rotZ+1)%360;

  glutPostRedisplay();
  glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
}

// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
