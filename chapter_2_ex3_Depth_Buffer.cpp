///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <GL/freeglut.h>
#include <cmath>

#define PI 3.14

void drawDisc(float R, float X, float Y, float Z){
	static int N = 100; // #vertices.
	float t = 0.0;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(X,Y,0); //center point
	for (int i = 0; i <= N; ++i){
		glVertex3f(X + R * cos(t), Y + R * sin(t), Z);
		t += 2 * PI / N;
	}
	glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glEnable(GL_DEPTH_TEST); //where it's checking the distance between vertex dustances, closes/farther

	glColor3f(0.0, 1.0, 0.0);
	drawDisc(20.0, 50.0, 50.0, 0.0); //small green circle

	glColor3f(1.0, 0.0, 0.0);
	drawDisc(40.0, 50.0, 50.0, 0.0); //big red circle

    /*Red & Green circles are the same size*/
//    glColor3f(0.0, 1.0, 0.0);        //green
//    drawDisc(20.0, 55.0, 50.0, 0.9); //greater Z means closer to the viewer
//
//    glColor3f(1.0, 0.0, 0.0);        //red
//    drawDisc(20.0, 45.0, 50.0, 0.5); //
    
    //Tesing with glEnable(GL_DEPTH_TEST) & glDisable(GL_DEPTH_TEST)
//    glColor3f(0.0, 0.0, 1.0);
//    drawDisc(20.0, 50.0, 55.0, 0.7);
    
//	glDisable(GL_DEPTH_TEST);
    
    //Tesing with glEnable(GL_DEPTH_TEST) & glDisable(GL_DEPTH_TEST). If put after the glDisable(GL_DEPTH_TEST); then the circle is not being enabled.
//    glColor3f(0.0,0.0, 1.0);
//    drawDisc(20.0, 50.0, 55.0, 0.7);
	
    glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

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
	default:
		break;
	}
}

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out chapter_2_ex3_Depth_Buffer.cpp
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    //GLUT_SINGLE: you can picture your code drawing directly to the display.
    //GLUT_DOUBLE: you can picture having 2 budders. One of them is always visible, the other one is not.
    //GLUT_DEPTH: for every pixels keep the depth information as well == enanbles the usage of the depth buffer, Z-buffer/
    
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("square.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
