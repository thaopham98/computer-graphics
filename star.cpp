///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <GL/freeglut.h>
#include <cmath>

int objx = 50;
int objy = 50;
//int numVertices = 250;
void drawStar(float x, float y, int size){
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x, y, 0.0);              //0
    glVertex3f(x-size*.27, y+size/4, 0.0);//1
    glVertex3f(x, y+size, 0.0);         //2
    glVertex3f(x+size*.27, y+size/4, 0.0);//3
    glVertex3f(x+size, y+size/4, 0.0);  //4
    glVertex3f(x+size*.4, y-size/5, 0.0);//5
    glVertex3f(x+size*0.7, y-size, 0.0);//6
    glVertex3f(x, y-size/2, 0.0);       //7
    glVertex3f(x-size*0.7, y-size, 0.0);//8
    glVertex3f(x-size*.4, y-size/5, 0.0);//9
    glVertex3f(x-size, y+size/4, 0.0);  //10
    glVertex3f(x-size/4, y+size/4, 0.0);//11
    glEnd();
}
//void cir(){
//    glBegin(GL_LINE_LOOP);
//    for(i = 0; i < numVertices; ++i) {
//     }
//    glColor3f((float)rand()/(float)RAND MAX, (float)rand()/(float)RAND MAX,
//    (float)rand()/(float)RAND MAX); glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0); t += 2 * PI / numVertices;
//    glEnd();
//}
// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw a polygon with specified vertices.
	glColor3f(0,0,0);
    drawStar(objx, objy, 18);
    
    glColor3f(1.0,0.0,0.0);
    drawStar(objx, objy, 15);
    
//    cir(objx,objy, 18);

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

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out star.cpp
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("5pointed_star.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
