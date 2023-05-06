///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

static float mc[] = { 0,0,0 }; //my color for the menu
float p_x = 250;
float p_y = 250; //mouse position

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    
    glColor3f(0.7,0.3,0.9);
	glColor3f(mc[0], mc[1], mc[2]);
    
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(100, 100, 0);
	glVertex3f(100, 400, 0);
	glVertex3f(400, 100, 0);
	glVertex3f(400, 400, 0);
	glEnd();

	glFlush();
}

void menuFunc(int id) {
	if (id == 1) {
		mc[0] = 1; mc[1] = 0; mc[2] = 0;
	}
	else if (id == 2) {
		mc[0] = 0; mc[1] = 1; mc[2] = 0;
	}
	else if (id == 3) {
		mc[0] = 0; mc[1] = 0; mc[2] = 1;
	}

	//After making changes on objects we can call print new scene
	glutPostRedisplay();
}

void makeMenu(void){
	glutCreateMenu(menuFunc);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);

	glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to a mouse button.
}

// Initialization routine.
void setup(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	makeMenu();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Here we want to match window coordinates and 3D space coordinates
	//Because we want to match mouse position (in window pixel coordinates)
	//and object coordinates (in 3D viewing cube)
	glOrtho(0.0, w, 0.0, h, -1.0, 1.0);

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

void motionFunc(int x, int y) {
	p_x = x;
	p_y = 500-y;

	if (p_x >= 100 && p_x <= 400 && p_y >= 100 && p_y <= 400) // if the mouse is in this window...
		glutAttachMenu(GLUT_RIGHT_BUTTON); //,... the right mouse the attached. == we can right click the mouse to pop up the menu
	else // if the mouse is not in the window,...
		glutDetachMenu(GLUT_RIGHT_BUTTON);  // ... then the mouse is detached.
}

// Main routine.
int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Popup Menu.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	glutPassiveMotionFunc(motionFunc); // activated when the mouse is moved

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
