#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>

#define PI 3.14159265
#define N 4

static float modelviewMatrix[4][4];
static float P1[4][N] = {
	{0,  0,  0,  0},
  {10,  10, -10, -10},
	{10, -10, -10,  10},
	{1,  1,  1,  1}
};
static float P2[4][N];

float d2r(int degree){return ((PI / 180.0) * degree);} //degree to radians

void writeBitmapString(void *font, const char *str){
	int i = 0;
	while(str[i] != '\0')
		glutBitmapCharacter(font, str[i++]);
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

void displayModelviewMatrix(void){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			printf("% 6.2f ", modelviewMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void rotX(float angle){
	modelviewMatrix[0][0] = 1;
	modelviewMatrix[1][1] = cos(d2r(angle));
	modelviewMatrix[1][2] = -sin(d2r(angle));
	modelviewMatrix[2][1] = sin(d2r(angle));
	modelviewMatrix[2][2] = cos(d2r(angle));
	modelviewMatrix[3][3] = 1;
}
void rotY(float angle){
	modelviewMatrix[0][0] = cos(d2r(angle));
	modelviewMatrix[0][2] = sin(d2r(angle));
	modelviewMatrix[1][1] = 1;
	modelviewMatrix[2][0] = -sin(d2r(angle));
	modelviewMatrix[2][2] = cos(d2r(angle));
	modelviewMatrix[3][3] = 1;
}
void rotZ(float angle){
	modelviewMatrix[0][0] = cos(d2r(angle));
	modelviewMatrix[0][1] = -sin(d2r(angle));
	modelviewMatrix[1][0] = sin(d2r(angle));
	modelviewMatrix[1][1] = cos(d2r(angle));
	modelviewMatrix[2][2] = 1;
	modelviewMatrix[3][3] = 1;
}

void matMul(float P2[4][N], float P1[4][N]){
	for(int i=0;i<4;i++){
		for(int j=0;j<N;j++){
				P2[i][j]=0;
				for(int k=0;k<4;k++)
						P2[i][j]+=modelviewMatrix[i][k]*P1[k][j];
		}
	}
}

void drawP1(){
	glColor3f(1,0,0);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		for(int i=0; i<4; i++)
			glVertex3f(P1[0][i],P1[1][i],P1[2][i]);
	glEnd();
}
void drawP2(){
	glColor3f(0,1,0);
	glLineWidth(3);
	glBegin(GL_LINE_LOOP);
		for(int i=0; i<4; i++)
			glVertex3f(P2[0][i],P2[1][i],P2[2][i]);
	glEnd();
}

// Drawing routine.
void drawScene(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(10, 15, 25, 0, 0, 0, 0, 1.0, 0.0);
	drawAxis(20);
	//-----------------------------------------------

	rotY(30); //rotY(30), rotZ(30)

	std::cout << "My Modelview Matrix" << std::endl;
	displayModelviewMatrix();

	//multiply modelview matrix with P1 and find P2
	matMul(P2,P1);

	drawP1();
	drawP2();

	//------------------------------------------------
	glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
	switch (key)
	{
		case 27:
			exit(0);
			break;
		default:
			break;
	}
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
	gluPerspective(90, 1, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);
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

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
