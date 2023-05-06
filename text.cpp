#include <GL/freeglut.h>
#include <GL/glut.h>
#include <cmath>

//Center coordinate
//int objx = 250;
//int objy = 250;
//int n = 100;
//static char *objName; // pointer to object name

// Routine to draw a stroke character string.
void writeStrokeString(void *font, char *string)
{
    char *c;

    for (c = string; *c != '\0'; c++) glutStrokeCharacter(font, *c);
}



void writeObjectName(){
    glPushMatrix();
    glTranslatef(10.0, 10.0, 0.0); // position
    glRotatef(0.0, 0.0, 0.0, 0.0); // rotation
    glScalef(0.025, 0.025, 0.025); // big/small
    
    writeStrokeString(GLUT_STROKE_ROMAN," is Selected. Press \"SPACE\" to Spin");
    // To be more general:
//    writeStrokeString(GLUT_STROKE_ROMAN,objName);
    
    glPopMatrix();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
    
    
    
    glColor3f(0.0, 0.0, 0.0);
    writeObjectName();
    
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

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out text.cpp
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("text.cpp");

	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();
}
