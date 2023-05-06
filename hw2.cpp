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

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// Draw a polygon with specified vertices.
    
    //Outer Circle
    static float R = 63.0; // Radius of circle.
    static float X = 50.0; // X of center.
    static float Y = 50.0; // Y of center.
    static int numVertices = 200; // #vertices.
    glColor3f(0.8,0.8,0.8);
    float t = 0;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < numVertices; i++)
    {
        glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
        t += 2 * PI / numVertices;
    }
    glEnd();

    //Inner Circle
    static float r = 57.0; // Radius of circle.
    glColor3f(1.0, 1.0, 1.0);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < numVertices; i++)
    {
        glVertex3f(X + r * cos(t), Y + r * sin(t), 0.0);
        t += 2 * PI / numVertices;
    }
    glEnd();
    
    //ARROW
    glColor3f(0.5,0.35,0.05);
    glBegin(GL_POLYGON);
    glVertex3f(45.0,23.0,0.0);
    glVertex3f(55.0,23.0,0.0);
    glVertex3f(55.0,70.0,0.0);
    glVertex3f(45.0,70.0,0.0);
    glEnd();
    glColor3f(0.5,0.35,0.05);
    glBegin(GL_POLYGON);
    glVertex3f(41.0,70.0,0.0); //Left
    glVertex3f(50.0,77.0,0.0); //Top
    glVertex3f(59.0,70.0,0.0); //Right
    glEnd();
    
    //TRIANGLE
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    //    glVertex3f(20.0, 20.0, 0.0);
    //    glVertex3f(80.0, 20.0, 0.0);
    //    glVertex3f(50.0, 80.0, 0.0);
    glVertex3f(41.0, 85.0, 0.0); //Left
    glVertex3f(50.0, 103.0, 0.0); //Top
    glVertex3f(59.0, 85.0, 0.0); //Right
    glEnd();
    
    //DIAMOND
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(41.0, 4.0, 0.0); //Left
    glVertex3f(50.0, -4.0, 0.0); //Bottom
    glVertex3f(59.0, 4.0, 0.0); //Right
    glVertex3f(50.0, 14.0, 0.0); //Top
    glEnd();
    
    //CROSS
    //HORIZONTAL RECTANGLE
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(80.0,53.0,0.0);
    glVertex3f(98.0,53.0,0.0);
    glVertex3f(98.0,47.0,0.0);
    glVertex3f(80.0,47.0,0.0);
    glEnd();
    //VERTICAL RECTANGLE
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex3f(86.0,59.0,0.0);
    glVertex3f(92.0,59.0,0.0);
    glVertex3f(92.0,41.0,0.0);
    glVertex3f(86.0,41.0,0.0);
    glEnd();
    
    //STAR
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(2.0,41.0,0.0);
    glVertex3f(9.0,59.0,0.0);
    glVertex3f(9.0,45.5,0.0);
    glVertex3f(16.0,41.0,0.0);
    glVertex3f(9.0,59.0,0.0);
    glEnd();
    
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 54.5, 0.0);
    glVertex3f(18.0, 54.5, 0.0);
    glVertex3f(9.0, 45.5, 0.0);
    glEnd();
    
	glFlush();
    
}

// Initialization routine.
void setup(void)
{
    //setting a white blackground to draw on
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 120.0, -20.0, 120.0, -1.0, 1.0);

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

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out hw2.cpp
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("square.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
