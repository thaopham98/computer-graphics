#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include<stdio.h>
#include<GL/glut.h>
#include<unistd.h>
#include <ctime>
#include <vector>

#define PI 3.14
#define MSEC_PER_FRAME 30

bool pauseMotion = false;
static int width, height;
//The center point
int obj_x = 250;
int obj_y = 250;

//The mouse postion
float m_x = 250;
float m_y = 250;

int size = 60;
//float a, b, c;
static float mc[] = { 0,0,0 };
//static float mc[] = { a,b,c };
int bigCircle = size * 7;
float Radius = bigCircle/2;

float smallCircle = bigCircle - (size/3);
float smallRadius = smallCircle/2;
int numVertices = 250;

int rot = 5;
int totalDegress = 0;

    //Circle
void drawCirle(float R, float X, float Y, int numVertices, int size){
    float t = 0;
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < numVertices; i++)
    {
        glVertex3f(X + R * cos(t), Y + R * sin(t), 0.0);
        t += 2 * PI / numVertices;
    }
    glEnd();
}

    // Arrow
void drawArrow(float x, float y, int size){
    glBegin(GL_POLYGON);
    glVertex3f(x-(size/4), y-(1.5*size), 0.0); //left bottom
    glVertex3f(x+(size/4), y-(1.5*size), 0.0); //right bottom
    glVertex3f(x+(size/4), y+(size*7/6), 0.0); //right top
    glVertex3f(x-(size/4), y+(size*7/6), 0.0); //left top
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(x+size/2, y+(size*7/6),0.0); //right
    glVertex3f(x-size/2, y+(size*7/6),0.0); //left
    glVertex3f(x, y+(size*3/2), 0.0); //top
    glEnd();
}

    //Diamond
void drawDiamond(float x, float y, int size){
    glBegin(GL_POLYGON);
    glVertex3f(x, y-size*2.0, 0.0); //top
    glVertex3f(x-size/2, y-size*2.5, 0.0); //left
    glVertex3f(x, y-size*3.0, 0.0); //bottom
    glVertex3f(x+size/2, y-size*2.5, 0.0); //right
    glEnd();
}

    //TRIANGLE
void drawTriangle(float x, float y, int size){
    glBegin(GL_TRIANGLES);
    glVertex3f(x+size/2, y+size*2.0, 0.0); //right
    glVertex3f(x-size/2, y+size*2.0, 0.0); //left
    glVertex3f(x, y+(size*3.0), 0.0); //top
    glEnd();
}

void drawCross(float x, float y, int size){
    glBegin(GL_POLYGON);// horizontal
    glVertex3f(x+size*2.75, y + size/2, 0.0); // top left
    glVertex3f(x+size*2.75, y - size/2, 0.0); // bottom left
    glVertex3f(x+size*2.5, y - size/2, 0.0); // bottom right
    glVertex3f(x+size*2.5, y + size/2, 0.0); // top right
    glEnd();
    
    glBegin(GL_POLYGON); // vertical
    glVertex3f(x+size*2.10, y+size/8, 0.0); //top left
    glVertex3f(x+size*2.10, y-size/8, 0.0); //bottom left
    glVertex3f(x+size*3.15, y-size/8, 0.0); //bottom right
    glVertex3f(x+size*3.15, y+size/8, 0.0); //top right
    glEnd();
}

void drawStar(float x, float y, int size){
    glBegin(GL_TRIANGLES);
    glVertex3f(x-size*2, y+size/4, 0.0); //R
    glVertex3f(x-size*2.5, y-size/7, 0.0);
    glVertex3f(x-size*3, y+size/4, 0.0); //L
    glEnd();
    
    glBegin(GL_POLYGON);
    glVertex3f(x-size*2.5, y-(size/4), 0.0); //mid bottom
    glVertex3f(x-size*2.20, y-size/2, 0.0);
    glVertex3f(x-size*2.5, y+size/2, 0.0); //top
    glVertex3f(x-size*2.80, y-size/2, 0.0);
    glEnd();
    
}


void writeBitmapString(void *font, char *string)
{
    for (char* c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}
void drawText(float x, float y, int size){
    glRasterPos3f(x-size*7/2, y-size*3.9, 0.0);
    writeBitmapString(GLUT_BITMAP_8_BY_13," is Selected. Press \"SPACE\" to Spint");
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //drawing gray circle
    glColor3f(0.8, 0.8, 0.8);
    drawCirle(Radius, obj_x, obj_y, numVertices,bigCircle);
    
    //drawing white circle
    glColor3f(1.0, 1.0, 1.0);
    drawCirle(smallRadius, obj_x, obj_y, numVertices, smallCircle);
    
    //drawing black dot
    glColor3f(0.0, 0.0, 0.0);
    drawCirle(1, obj_x, obj_y, numVertices, 2);
    
    //drawing red cross
    glColor3f(1.0, 0.0, 0.0);
    drawCross(obj_x, obj_y, size);
    
    //drawing yellow diamond
    glColor3f(1.0, 1.0, 0.0);
    drawDiamond(obj_x, obj_y, size);

    //drawing green star
    glColor3f(0.0, 1.0, 0.0);
//    glColor3f(mc[0], mc[1], mc[2]);
    drawStar(obj_x, obj_y, size);
    
    //drawing blue triangle
    glColor3f(0.0,0.0,1.0);
    drawTriangle(obj_x, obj_y, size);
    
//    glColor3f(0.0, 0.0, 0.0);
//    drawText(obj_x, obj_y, size);
    
    
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    drawCirle(size/2, obj_x, obj_y, numVertices, smallCircle);
//    drawStar(obj_x, obj_y, size);
    
    //drawing arrow
    glColor3f(0.5, 0.35, 0.05);
//    glTranslatef(obj_x, obj_y, 0);
//    glRotatef(rot, 0, 0, 1);
    drawArrow(obj_x,obj_y,size);
    
    glFlush();
}
void timerFunc(int value) {

    if (!pauseMotion) {
        //obj_x += 1;
        //obj_y -= 1;
        if(rot < totalDegress)
            rot = (rot + 1) % 360;
    }

    glutPostRedisplay();
    glutTimerFunc(MSEC_PER_FRAME, timerFunc, value);
}
void mouseControl(int button, int state, int x, int y)
{
//    obj_x = x;
//    obj_y = 500-y;

    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
    {
        std::cout << "The coordinate of x is " << x << "The coordinate of y is " << y;
        
        drawTriangle(x, y, size);
    }

    glutPostRedisplay();
}

//void menuFunc(int id) { // CHANGING THE COLORS
//    if (id == 1) {
//        mc[0] = 0.7; mc[1] = 0.3; mc[2] = 0.9;
//    }
//    else if (id == 2) {
//        mc[0] = 1; mc[1] = 0.6; mc[2] = 0.1;
//    }
//    else if (id == 3) {
//        mc[0] = 0; mc[1] = 1; mc[2] = 1;
//    }
//    else if (id == 4) {
//        mc[0] = 1; mc[1] = 0.5; mc[2] = 1;
//    }
//    //After making changes on objects we can call print new scene
//    glutPostRedisplay();
//}

//void makeMenu(void){ //CREATE THE POPUP MENU
//    glutCreateMenu(menuFunc);
//    glutAddMenuEntry("Purple", 1); //1ST OPTION
//    glutAddMenuEntry("Orange", 2); //2ND OPTION
//    glutAddMenuEntry("Cyan", 3);   //3RD OPTION
//    glutAddMenuEntry("Pink", 4);   //4TH OPTION
//    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to a right button.
//}

// Initialization routine.
void setup(void)
{
    //setting a white blackground to draw on
    glClearColor(1.0, 1.0, 1.0, 0.0);
//    makeMenu();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
    width = w; height = h;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
    int randNum;
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case ' ':
        if (pauseMotion) pauseMotion = false;
        else pauseMotion = true;
        //for the arrow to move
        break;
    case 'r':
        rot = 0;
        randNum = rand() % 10;
        totalDegress = randNum * 45;
        break;
    default:
        break;
    }
}

//void motionFunc(int x, int y){
//    m_x = x;
//    m_y = 500 - y;
//
//    if (/*m_x>=x-size*3 && m_x>=x-size*2 && m_y>=y-size/2 && m_y>=y+size/2 */
//        drawTriangle(m_x, y, size))
//        glutAttachMenu(GLUT_RIGHT_BUTTON);
//    else
//        glutDetachMenu(GLUT_RIGHT_BUTTON);
//
//
//}

// /Applications/Studying/FA21/CSCI_4550
// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out main.cpp
int main(int argc, char **argv)
{
    srand(time(0));

    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    glutCreateWindow("main.cpp");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    
//    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);
    
    glutMouseFunc(mouseControl);
    
    glutPassiveMotionFunc(motionFunc);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    setup();

    glutMainLoop();
}
