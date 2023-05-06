#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

float obj_x = 0.0, obj_y = 0.0;

//To change the color of the object
//float color = 0;

void drawObject(float x,float y){
	glBegin(GL_POLYGON);
	glVertex3f(x-10.0, y-10.0, -40.0);
	glVertex3f(x+10.0, y-10.0, -40.0);
	glVertex3f(x+10.0, y+10.0, -40.0);
	glVertex3f(x-10.0, y+10.0, -40.0);
	glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the buffers including the depth buffer.

    //changing the color of the object
//    if (color == 0)
//        glColor3f(0,1,0);
//    else
//        glColor3f(1,0,0);
    
    glColor3f(0,1,0);
	drawObject(obj_x,obj_y);

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
	gluPerspective(90,w/h,5,100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'a':
			obj_x-=1;
			break;
		case 'd':
			obj_x+=1;
			break;
		case 'w':
			obj_y+=1;
			break;
		case 's':
			obj_y-=1;
			break;
		case 27:
			exit(0);
			break;
//        case 'c': // changing the color of the object
//            color = 1;
            break;
		default:
			break;
	}
	//std::cout << eyeX << " " << eyeY << std::endl;
	glutPostRedisplay();
}

// Callback routine for non-ASCII key entry.
/*void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_DOWN)
    {
        obj_y-=1;
    }
    if (key == GLUT_KEY_LEFT)
    {
        obj_x-=1;
    }
    if (key == GLUT_KEY_UP)
    {
        obj_y+=1;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        obj_x+=1;
    }

    glutPostRedisplay();
}*/

//  g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out main.cpp
// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("GLUT PostRedisplay Example");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
    //glutSpecialFunc(specialKeyInput);
    
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
