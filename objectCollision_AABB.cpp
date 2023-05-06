#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

#define MSEC_PER_FRAME 10

//Here we are defining two axis-aligned rectangular objects
//object 1 is stationary and object 2 is moving from different directions
//checkCollision() function can detect all collisions!

float obj1[] = {250,250,0};
float obj1SizeX = 40;
float obj1SizeY = 40;

float obj2[] = {400,110,0};
float obj2SizeX = 20;
float obj2SizeY = 20;

bool objCollision = false;
bool pauseGame = false;

void writeBitmapString(void *font, char *string){
	for (char* c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
}

void drawEndGameMessage(char* msg){

	glPushMatrix();
		glLoadIdentity();
		glTranslatef(250,350,0);
		glScalef(2,1,1);
		glColor3f(1,0,0);glutSolidCube(100);
	glPopMatrix();

	glColor3f(1,1,1);
	glWindowPos3f(170, 350, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, msg);
}

// Drawing routine.
void drawScene(void){
	glClear(GL_COLOR_BUFFER_BIT);

	//------------------------------------------------
	glLoadIdentity();

	glPushMatrix();
	glColor3f(0,0,1);
	glTranslatef(obj1[0],obj1[1],obj1[2]);
	glScalef(obj1SizeX,obj1SizeY,1);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0,1,0);
	glTranslatef(obj2[0],obj2[1],obj2[2]);
	glScalef(obj2SizeX,obj2SizeY,1);
	glutSolidCube(1);
	glPopMatrix();

	if(objCollision)
		drawEndGameMessage("Collision!");

	//-------------------------------------------------
	glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
	switch (key)
	{
		case 27:
			exit(0);
			break;
		case 'a':
			obj2[0]-=40;
			break;
		case 'd':
			obj2[0]+=40;
			break;
		default:
			break;
	}
}

bool checkCollision(){
	if(obj1[0]-obj1SizeX/2 <= obj2[0]+obj2SizeX/2 &&
		 obj1[0]+obj1SizeX/2 >= obj2[0]-obj2SizeX/2 &&
     obj1[1]-obj1SizeY/2 <= obj2[1]+obj2SizeY/2 &&
		 obj1[1]+obj1SizeY/2 >= obj2[1]-obj2SizeY/2)
    return true;
	else
		return false;
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){

	//object 2 is moving towards object 1 from different directions
	if(!pauseGame){
		obj2[1]++;
		obj2[0]--;
		objCollision = checkCollision();
	}

	if(objCollision)
		pauseGame = true;

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
	glOrtho(0, w, 0, h, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main routine.
int main(int argc, char **argv){
	srand(time(0));

	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Object Collision Example 1 (AXIS-ALIGNED)");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
