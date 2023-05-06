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
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

// Globals.
static int width, height; // OpenGL window size.
static float pointSize = 5.0; // Initial point size.

// Point class.
class Point
{
	public:
		float xVal, yVal; // x and y co-ordinates of point.
		Point(float x, float y){
			xVal = x; yVal = y;
		}
		Point() {};
};

// Vector of points.
std::vector<Point> points;

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
 
	// Loop through the points array drawing each point.
	glPointSize(pointSize);
	glBegin(GL_POINTS);
		for (auto point : points) {
			glVertex3f(point.xVal, point.yVal, 0.0);
		}
	glEnd();

	glBegin(GL_LINE_STRIP);
		for (auto point : points) {
			glVertex3f(point.xVal, point.yVal, 0.0);
		}
	glEnd();

	glFlush();
}

// Mouse callback routine.
void mouseControl(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		points.push_back(Point(x, height - y) );
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		exit(0);

	glutPostRedisplay();
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
	case 'c':
		points.clear();
		glutPostRedisplay(); // calling the display function indirectly instead of calling the drawScenc function yourself
		break;
	case 'd':
		points.push_back(Point(250, 250));
		glutPostRedisplay();
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
	glutCreateWindow("Mouse and Keyboard Example");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);

	//Register the keyboard callback function
	glutKeyboardFunc(keyInput);

	// Register the mouse callback function.
	glutMouseFunc(mouseControl);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
