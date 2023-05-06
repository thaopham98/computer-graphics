#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

#define MSEC_PER_FRAME 10
#define NUMBER_OF_BALLS 5

#define NO_WALL_COLLISION 0
#define LEFT_WALL 1
#define RIGHT_WALL 2
#define TOP_WALL 3
#define BOTTOM_WALL 4

bool pauseGame = false;

class ball {
	public:
		float _x;
		float _y;
		float _z;
		float _vx;
		float _vy;
		float _vz;
		float _radius;
		float* _color;

	public:
		ball(){}
		ball(float x, float y, float vx,float vy,float r) {
			_x = x; _y = y; _z = 0;
			_vx = vx; _vy = vy; _vz = 0;
			_radius = r;
		}

		void move() { 
			_x += _vx;
			_y += _vy;
		}

		int checkWallCollision() {
			if (_x >= 500 - _radius)
				return RIGHT_WALL;
			else if (_x <= 0 + _radius)
				return LEFT_WALL;
			else if (_y >= 500 - _radius)
				return TOP_WALL;
			else if (_y <= 0 + _radius)
				return BOTTOM_WALL;
			else
				return NO_WALL_COLLISION;
		}

		bool checkObjCollision(ball b) {
			float r = _radius + b._radius;
			float distSq = ((_x - b._x) * (_x - b._x)) +
							((_y - b._y) * (_y - b._y)) +
							((_z - b._z) * (_z - b._z));

			if (r * r >= distSq)
				return true;
			else
				return false;
		}

};

ball ballArray[NUMBER_OF_BALLS];

void constructAllBalls() {
	for (int i = 0; i < NUMBER_OF_BALLS; i++) {
		ballArray[i]._x = rand() % 400 + 50;
		ballArray[i]._y = rand() % 400 + 50;
		ballArray[i]._z = 0;
		ballArray[i]._vx = rand() % 8 - 4;
		ballArray[i]._vy = rand() % 8 - 4;
		ballArray[i]._vz = 0;
		ballArray[i]._radius = rand()%20+10;
		ballArray[i]._color = new float[3];
		ballArray[i]._color[0] = 1.0 / ((rand() % 10) + 1);
		ballArray[i]._color[1] = 1.0 / ((rand() % 10) + 1);
		ballArray[i]._color[2] = 1.0 / ((rand() % 10) + 1);
	}
}

void handleCollision(ball &b1, ball &b2) {
	float tmp = b1._vx;
	b1._vx = b2._vx;
	b2._vx = tmp;
	
	tmp = b1._vy;
	b1._vy = b2._vy;
	b2._vy = tmp;
}

// Drawing routine.
void drawScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//------------------------------------------------
	glLoadIdentity();

	for (int i = 0; i < NUMBER_OF_BALLS; i++) {
		glColor3fv(ballArray[i]._color);
		glPushMatrix();
		glTranslatef(ballArray[i]._x, ballArray[i]._y, ballArray[i]._z);
		glScalef(ballArray[i]._radius, ballArray[i]._radius, 1);
		glutSolidSphere(1, 100, 100);
		glPopMatrix();
	}

	//-------------------------------------------------
	glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case ' ':
		pauseGame = (pauseGame + 1) % 2;
	default:
		break;
	}
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value) {

	if (!pauseGame) {
		for (int i = 0; i < NUMBER_OF_BALLS; i++) {

			ballArray[i].move();

			int wall = ballArray[i].checkWallCollision();
			if (wall == LEFT_WALL || wall == RIGHT_WALL)
				ballArray[i]._vx *= -1;
			else if (wall == TOP_WALL || wall == BOTTOM_WALL)
				ballArray[i]._vy *= -1;

			for (int j = i + 1; j < NUMBER_OF_BALLS; j++) {
				bool objCol = ballArray[i].checkObjCollision(ballArray[j]);
				if (objCol)
					handleCollision(ballArray[i], ballArray[j]);
			}
		}
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
	glOrtho(0, w, 0, h, -100, 100);
	//gluPerspective(90.0, 1, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Main routine.
int main(int argc, char** argv) {
	srand(time(0));
	constructAllBalls();

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
