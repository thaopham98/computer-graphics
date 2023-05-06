///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <GL/freeglut.h>


void drawScene(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0, 0.0, 0.0);
  
  glBegin(GL_LINE_LOOP);
    glVertex3f(1,1,0);
    glVertex3f(3,1,0);
    glVertex3f(4,4,0);
    glVertex3f(6,4,0);
    glVertex3f(7,1,0);
    glVertex3f(9,1,0);
    glVertex3f(6,10,0);
    glVertex3f(4,10,0);
  glEnd();
  
  glBegin(GL_LINE_LOOP);
    glVertex3f(4.0,5.0,0.0);
    glVertex3f(6.0,5.0,0.0);
    glVertex3f(5.0,8.0,0.0);
  glEnd();
  
  glFlush();

}

// Drawing routine.
//void drawScene(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glColor3f(0,0,0);

    
    
    
	// Draw a polygon with specified vertices.
//	 glBegin(GL_POLYGON);
//	 glVertex3f(20.0, 20.0, 0.0);
//	 glVertex3f(80.0, 20.0, 0.0);
//	 glVertex3f(80.0, 80.0, 0.0);
//	 glVertex3f(50.0, 90.0, 0.0);
//	 glVertex3f(20.0, 80.0, 0.0);
//	 glEnd();

	//---------------------------------------------------
	// Triangle Clipping
// 	glBegin(GL_POLYGON);
//	glVertex3f(20.0, 20.0, 0.0);
//	glVertex3f(80.0, 20.0, 0.0);
//	glVertex3f(80.0, 80.0, 0.0);
//	glEnd();

	//---------------------------------------------------
	//Two squares in different colors
/* 	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(20.0, 20.0, 0.0);
	glVertex3f(70.0, 20.0, 0.0);
	glVertex3f(70.0, 70.0, 0.0);
	glVertex3f(20.0, 70.0, 0.0);
	glEnd();
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(40.0, 40.0, 0.5);
	glVertex3f(90.0, 40.0, 0.5);
	glVertex3f(90.0, 90.0, 0.5);
	glVertex3f(40.0, 90.0, 0.5);
	glEnd(); */

	//---------------------------------------------------
	//Colored Vertices
/* 	glBegin(GL_POLYGON);
	glColor3f(0.0, 1.0, 0.0); glVertex3f(20.0, 20.0, 0.0); //green
	glColor3f(1.0, 1.0, 0.0); glVertex3f(80.0, 20.0, 0.0); //yellow
	glColor3f(1.0, 0.0, 0.0); glVertex3f(80.0, 80.0, 0.0); //red
	glColor3f(0.0, 0.0, 1.0); glVertex3f(20.0, 80.0, 0.0); //blue
	glEnd(); */

	//---------------------------------------------------
	//Polygone Mode, LINE, FRONT, BACK
	// glColor3f(1,1,0);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// glBegin(GL_TRIANGLE_STRIP);
	// glVertex3f(10.0, 90.0, 0.0);
	// glVertex3f(10.0, 10.0, 0.0);
	// glVertex3f(35.0, 75.0, 0.0);
	// glVertex3f(30.0, 20.0, 0.0);
	// glVertex3f(90.0, 90.0, 0.0);
	// glVertex3f(80.0, 40.0, 0.0);
	// glEnd();

	//---------------------------------------------------
	//Annulus Shape
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glBegin(GL_TRIANGLE_STRIP);
//	glVertex3f(30.0, 70.0, 0.0);
//	glVertex3f(10.0, 90.0, 0.0);
//	glVertex3f(70.0, 70.0, 0.0);
//	glVertex3f(90.0, 90.0, 0.0);
//	glVertex3f(70.0, 30.0, 0.0);
//	glVertex3f(90.0, 10.0, 0.0);
//	glVertex3f(30.0, 30.0, 0.0);
//	glVertex3f(10.0, 10.0, 0.0);
//	glVertex3f(30.0, 70.0, 0.0);//vertex 1
//	glVertex3f(10.0, 90.0, 0.0);//vertex 2
//	glEnd();

//	glFlush();
//}

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

// g++ -framework OpenGL -lGLUT -I /opt/X11/include -L /opt/X11/lib -w -o out chapter2ex1.cpp
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("chapter2ex1.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
