#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define MSEC_PER_FRAME 10
#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

int rot=0;
bool pauseMotion = false;
int switchView = 0;

float d2r(int degree){return ((PI / 180.0) * degree);} //degree to radians

void writeBitmapString(void* font, const char* string){
	for (int i=0; string[i] != '\0'; i++)
		glutBitmapCharacter(font, string[i]);
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

void drawDisc(float R, float X, float Y, float Z, bool dash){
	if(dash) glBegin(GL_LINES);
	else glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= N; ++i){
			float t = 2 * PI * i / N;
			glVertex3f(X + cos(t) * R, Y, Z + sin(t) * R);
		}
	glEnd();
}
void drawRandomObjects(){
	int p = 17;
	glPushMatrix();
		glScalef(1,3,1);
		glPushMatrix();
			glTranslatef(p,1,0);
			glColor3f(0,0,0); glutWireCube(2);
			glColor3f(0,1,0); glutSolidCube(2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-p,1,0);
			glColor3f(0,0,0); glutWireCube(2);
			glColor3f(0,0,1); glutSolidCube(2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,1,-p);
			glColor3f(0,0,0); glutWireCube(2);
			glColor3f(0,1,1); glutSolidCube(2);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,1,p);
			glColor3f(0,0,0); glutWireCube(2);
			glColor3f(1,0,0); glutSolidCube(2);
		glPopMatrix();
	glPopMatrix();
}
void drawCar(){
	glPushMatrix();
		glTranslatef(0, 1, -2);
		glScalef(2,1,1);
		glColor3f(0,0,0);glutWireCube(2);
		glColor3f(1,0,1);glutSolidCube(2);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, 2, 1);
		glColor3f(0,0,0);glutWireCube(4);
		glColor3f(1,0,1);glutSolidCube(4);
	glPopMatrix();
}
void drawRoad(){
	glPushMatrix();
		glColor3f(0,0,0);
		drawDisc(10,0,0,0,false);
		drawDisc(16,0,0,0,false);
		drawDisc(13,0,0,0,true);
	glPopMatrix();
}

// Drawing routine.
void drawScene(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//------------------------------------------------
	glLoadIdentity();
	//gluLookAt(10,15,25,0,0,0,0,1,0);
	float p1[] = {13,5,0}; //eye position
	float p2[] = {13,5,-1}; //center position
	gluLookAt(p1[0]*cos(d2r(rot))+p1[2]*sin(d2r(rot)),
	          p1[1],
					 -p1[0]*sin(d2r(rot))+p1[2]*cos(d2r(rot)),
						p2[0]*cos(d2r(rot))+p2[2]*sin(d2r(rot)),
						p2[1],
					 -p2[0]*sin(d2r(rot))+p2[2]*cos(d2r(rot)),
						0, 1, 0);
	//------------------------------------------------
	drawAxis(20);
	drawRoad();
	drawRandomObjects();

	glPushMatrix();
		glRotatef(rot,0,1,0);
		glTranslatef(13,0,0);
		drawCar();
	glPopMatrix();
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
		case 's':
			switchView = (switchView+1)%2;
			break;
		default:
			break;
	}
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){

	if(!pauseMotion) rot = (rot+1)%360;

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
	glFrustum(-5.0, 5.0, -5.0, 5.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv){
	srand(time(0));

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
