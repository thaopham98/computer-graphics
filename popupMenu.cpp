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

#define RED 1
#define GREEN 2
#define BLUE 3
#define ORANGE 4

int size = 50;
bool triangle = false;
bool diamond = false;

static float triangleColor[3] = {0.0,0.0,1.0};
static float diamondColor[3] = {1.0,1.0,0.0};


void drawTriangle(float x, float y, int size){
    glBegin(GL_TRIANGLES);
    glVertex3f(x+size/2, y+size*2.0, 0.0); //right
    glVertex3f(x-size/2, y+size*2.0, 0.0); //left
    glVertex3f(x, y+(size*3.0), 0.0); //top
    glEnd();
}
void drawDiamond(float x, float y, int size){
    glBegin(GL_POLYGON);
    glVertex3f(x, y-size*2.0, 0.0); //top
    glVertex3f(x-size/2, y-size*2.5, 0.0); //left
    glVertex3f(x, y-size*3.0, 0.0); //bottom
    glVertex3f(x+size/2, y-size*2.5, 0.0); //right
    glEnd();
}

//static float mc[] = { 0,0,0 }; //my color for the menu
float p_x = 250;
float p_y = 250; //mouse position
float red;
float blue;
float green;

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
//    if (triangle){
//        glColor3f(red, green, blue);
//        glColor3f(1.0, 0.6, 1.0);
//        drawTriangle(p_x, p_y, 50);
//    }
//    else{
//        glColor3f(0.0,0.0,1.0);
//        drawTriangle(p_x, p_y, 50);
//    }
    glColor3fv(triangleColor);
    drawTriangle(p_x, p_y, size);
    
//    glColor3f(1.0,1.0,0.0);
    glColor3fv(diamondColor);
    drawDiamond(p_x, p_y, size);
    
	glFlush();
}
void processMenuEvents(int option){
    switch (option)
    {
        case RED:
            red = 1.0;
            green = 0.0;
            blue = 0.0;
            break;
        case GREEN:
            red = 0.0;
            green = 1.;
            blue = 0.0;
            break;
        case BLUE:
            red = 0.0;
            green = 0.0;
            blue = 1.0;
            break;
        case ORANGE:
            red = 1.0;
            green = 0.5;
            blue = 0.5;
            break;
    }
}

void createGlUTMenu(){
    int Menu;
    
    Menu = glutCreateMenu(processMenuEvents);
    
    glutAddMenuEntry("Red", RED);
    glutAddMenuEntry("Blue", BLUE);
    glutAddMenuEntry("Green", GREEN);
    glutAddMenuEntry("Orange", ORANGE);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouseController(int button, int state, int x, int y){
    p_x = x;
    p_y = y;
    
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if (200<=p_x && p_x<=300 && p_y<=150 && p_y>=70) //triangle
        {
            triangle = true;
        }
        else if (200<=p_x && p_x<=300 && 370<=p_y && p_y<=430)//diamond
            diamond = true;
    }
    
    if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
    {
        std::cout<<"\nRight click works\n";
        
    }
}

// Initialization routine.
void setup(void){
	glClearColor(1.0, 1.0, 1.0, 0.0);
	createGlUTMenu();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
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

//void motionFunc(int x, int y) {
//	p_x = x;
//	p_y = 500-y;
//
//	if (p_x >= 100 && p_x <= 400 && p_y >= 100 && p_y <= 400) // if the mouse is in this window...
//		glutAttachMenu(GLUT_RIGHT_BUTTON); //,... the right mouse the attached. == we can right click the mouse to pop up the menu
//	else // if the mouse is not in the window,...
//		glutDetachMenu(GLUT_RIGHT_BUTTON);  // ... then the mouse is detached.
//}

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

//	glutPassiveMotionFunc(motionFunc); // activated when the mouse is moved
//    createGlUTMenu();
    
    glutMouseFunc(mouseController);
    
	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
