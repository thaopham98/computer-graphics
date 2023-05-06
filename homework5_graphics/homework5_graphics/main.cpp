#include <GL/glew.h>
#include <GL/freeglut.h>

#include <cmath>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "getBMP.h"

#define MSEC_PER_FRAME 16.6

using namespace std;


bool pauseMotion = false; // moving

char chessboard[64][64][4];
bool light_ON = GL_TRUE;

int angle = 0.0;
int totalangle = 0.0;

float eyeX = 20.0;
float eyeY = 20.0;

float light0Pos[] = {-20,20,20,1};

float lightAmbient[] = { 1.0, 1.0, 1.0, 1.0/*Transperancy component*/}; //Ambient
float lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0}; //Diffuse
float lightSpecular[]= { 1.0, 1.0, 1.0, 1.0}; //Specular
//float globAmbient[]  = { 0.2, 0.2, 0.2, 1.0 }; //Global Ambient applies to the whole scene


// Material property vectors.
float matAmbient[] = { 0.2, 0.2, 0.2, 1.0 }; //Ambient Reflectance

float matDiffuse1[] = { 1.0, 1.0, 1.0, 1.0 }; //Diffuse Reflectance
float matDiffuse2[] = { 0.8, 0.0, 0.0, 1.0 };

float matSpecular1[] = { 1.0, 1.0, 1.0, 1.0 }; //Specular Reflectance
float matSpecular2[] = { 0.0, 0.0, 0.0, 1.0 };

float matShininess[]= { 20 };    //Shininess factor

float matEmission[] = { 0.0, 0.0, 0.0, 1.0 }; //Object Light Emission

unsigned int texture[7];
/*MARK: Texture */
void loadTextures()
{
    imageFile * image[1];

    image[0] = getBMP("/Applications/Studying/FA21/CSCI_4550/launch.bmp");

    glBindTexture(GL_TEXTURE_2D, texture[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//GL_CLAMP_TO_EDGE

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}
void createChessboard(void)
{
    int i, j;
    for (i = 0; i < 64; i++)
        for (j = 0; j < 64; j++)
            if ((((i / 8) % 2) && ((j / 8) % 2)) || (!((i / 8) % 2) && !((j / 8) % 2)))
            {
                chessboard[i][j][0] = 0x00;
                chessboard[i][j][1] = 0x00;
                chessboard[i][j][2] = 0x00;
                chessboard[i][j][3] = 0xFF;
            }
            else
            {
                chessboard[i][j][0] = 0xDD;
                chessboard[i][j][1] = 0xDD;
                chessboard[i][j][2] = 0xDD;
                chessboard[i][j][3] = 0xFF;
            }
}

// Routine to load a program-generated image as a texture.
void loadChessboardTexture()
{
    // Generate internal texture.
    createChessboard();

    // Create texture object texture[1].
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    // Specify image data for currently active texture object.
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, chessboard);

    // Set texture parameters for wrapping.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Set texture parameters for filtering.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}
/*MARK: Lighting*/
void setLightProperties()
{
    // Light0 properties.
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,lightSpecular);

    // Global ambient light, applied to all lights
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmbient);

    //set the position of light
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

    if(light_ON)    glEnable(GL_LIGHT0);
    else glDisable(GL_LIGHT0);
}

void setObjMaterialProperties(){
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse1);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular1);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

    /*
    There is only one object here.
    If there are multiple objects having different properties,
    these parameters must be set.
    */
}
void setObjMaterialProperties1(){
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);
}

/* MARK: Shape's Functions */
void writeBitmapString(void *font, char *string){
    for (char* c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}
void drawAxis(float size)
{
    glColor3f(1,0,0);
    glBegin(GL_LINES);
    glVertex3f(-size,0,0);
    glVertex3f(size,0,0);
    glEnd();
    
    glRasterPos3f(10, 0, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+X");
    
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex3f(0,-size,0);
    glVertex3f(0,size,0);
    glEnd();
    
    glRasterPos3f(0, 10, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Y");
    
    glColor3f(0,0,1);
    glBegin(GL_LINES);
    glVertex3f(0,0,-size);
    glVertex3f(0,0,size);
    
    glRasterPos3f(0, 0, -10);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Z");
    glEnd();
}

void drawObject()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    for (int y = -4; y < 3; y += 2) // FACE 1
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = -4; x < 6; x+=2)
        {
            glVertex3f(x, y, -4);
            glVertex3f(x, y + 2, -4);
        }
        glEnd();
    }

    for (int y = -4; y < 3; y += 2) // FACE 2
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int z = -4; z < 6; z+=2)
        {
            glVertex3f(4, y, z);
            glVertex3f(4, y + 2, z);
        }
        glEnd();
    }
}

void drawFace5()
{
    glColor3f(0, 1, 0);
    for (int z = -4; z < 3; z += 2) // FACE 5 = TOP
    {
        glBegin(GL_TRIANGLE_STRIP);
        for (int x = -4; x < 6; x += 2)
        {
            glVertex3f(x, 4, z);
            glVertex3f(x, 4, z+2);
        }
        glEnd();
    }
}


void drawCube(int size)
{
    glBegin(GL_POLYGON); // FACE 1 w/out light
    glColor3f(0.5, 0.5, 0);
    glTexCoord2f(0.0, 1.0);glVertex3f(size, size, -size);
    glTexCoord2f(1.0, 1.0);glVertex3f(-size, size, -size);
    glTexCoord2f(1.0, 1.0);glVertex3f(-size, -size, -size);
    glTexCoord2f(0.0, 0.0);glVertex3f(size, -size, -size);
    glEnd();

}

void drawBottom(int size)
{
//    glBindTexture(GL_TEXTURE_2D, texture[id]);
    glBegin(GL_POLYGON); // bottom
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, -size, -size);
    glEnd();
}

void drawFace3(int size)
{
    glBegin(GL_POLYGON);
    glTexCoord2f(0,0);glVertex3f(-size, -size, -size);
    glTexCoord2f(1,0);glVertex3f(-size, -size, size);
    glTexCoord2f(1,1);glVertex3f(-size, size, size);
    glTexCoord2f(0,1);glVertex3f(-size, size, -size);
    glEnd();
}

void drawFace4(int size)
{
    glBegin(GL_POLYGON); // BACK FACE
    glTexCoord2f(1,0);glVertex3f(size, -size, size);
    glTexCoord2f(1,1);glVertex3f(size, size, size);
    glTexCoord2f(0,1);glVertex3f(-size, size, size);
    glTexCoord2f(0,0);glVertex3f(-size, -size, size);
    glEnd();
}
/* MARK: Drawing routine */
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
//    gluLookAt(20.0, eyeY, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    gluLookAt(eyeX, eyeY, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    drawAxis(20);

    glRotatef(angle, 0.0, 1.0, 0.0);
    
    glEnable(GL_LIGHTING);
        
        setLightProperties();
        setObjMaterialProperties();
        
        glBindTexture(GL_TEXTURE_2D, texture[1]);
        glEnable(GL_TEXTURE_2D);
        
        drawObject(); // FACE 1 && FACE 2
                
    glDisable(GL_TEXTURE_2D);
    
    glDisable(GL_LIGHTING);
    
    glEnable(GL_LIGHTING);
        setObjMaterialProperties1();
        drawFace5();
    glDisable(GL_LIGHTING);
        
    

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glEnable(GL_TEXTURE_2D);
        drawFace3(4);
        drawFace4(4);
    glDisable(GL_TEXTURE_2D);
    
    
    drawBottom(4);
    
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

/* MARK: timerFunc() */
void timerFunc(int value) {

    if (!pauseMotion) {
        angle += 1;
    }
    if(angle > 360) angle = 0;
    glutPostRedisplay();
    glutTimerFunc(MSEC_PER_FRAME, timerFunc, value);
}
/* MARK: keyInput Function */
void keyInput(unsigned char key, int x, int y){
    switch (key)
    {
        case 27:
            exit(0);
            break;
        
        case ' ':
            if (pauseMotion)
                pauseMotion = false;
            else
                pauseMotion = true;
            break;
        
        case 'a':
        case 'A':
            light_ON = !light_ON;
            
            break;
            
        default:
            break;
    }
}

/* MARK: Special keyInput Function */
void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
    {
        angle -= 5.0;
        if(angle < 0.0)
            angle += 360.0;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        angle += 5.0;
        if (angle > 360.0) angle -= 360.0;
    }
    if (key == GLUT_KEY_UP)
    {
        eyeY += 5.0;
    }
    if (key == GLUT_KEY_DOWN)
    {
        eyeY -= 5.0;
    }
    glutPostRedisplay();
}

// Initialization routine.
/*MARK: setup() */
void setup(void){
    glClearColor(1.0, 1.0, 1.0, 0.0); //setting a white blackground to draw on screen
    glEnable(GL_DEPTH_TEST);
    
    glGenTextures(2, texture); // 4 textures
    
    /*Load external texture*/
    loadTextures(); //Loading image into texture format
    
    loadChessboardTexture();
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    
    glEnable(GL_TEXTURE_2D);
    
}

/* MARK: OpenGL window reshape routine */
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//    glFrustum(-5.0, 5.0, -5.0, 5.0, 5, 1000);
    gluPerspective(90.0, w/h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// /Applications/Studying/FA21/CSCI_4550/homework5_graphics/homework5_graphics
// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out main.cpp

/* MARK: Main Function */
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("main.cpp");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);
    
    glewExperimental = GL_TRUE;
    glewInit();
    setup();
    glutMainLoop();
}
