///////////////////////////////////////////////////////////////////////////////////////////////////////
// texturedSquare.cpp
//
// This stripped-down program shows how to load both external and program-generated images as textures.
//
// Interaction:
// Press the left and right arrow keys to rotate the square.
// Press space to toggle between textures.
// Press delete to reset.
//
// Sumanta Guha
//
// Texture Credits: See ExperimenterSource/Textures/TEXTURE_CREDITS.txt
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "getBMP.h"

#define PI 3.14159265
float d2r(int degree){return ((PI / 180.0) * degree);} //degree to radians

// Globals.
unsigned int texture[2]; // Array of texture ids.
char chessboard[64][64][4]; // Storage for chessboard image.
int id = 0; // Currently displayed texture id.

float angle = 0.0; // Angle to rotate textured square.

// Load external textures.
void loadTextures()
{
	// Local storage for image data.
	imageFile *image[1];

	// Load the image.
	image[0] = getBMP("./launch.bmp");

	// Create texture object texture[0].
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	// Specify image data for currently active texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image[0]->width, image[0]->height, 0,
	           	 GL_RGBA, GL_UNSIGNED_BYTE, image[0]->data);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);//GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);//GL_CLAMP_TO_EDGE

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Create 64 x 64 RGBA image of a chessboard.
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
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	// Specify image data for currently active texture object.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, chessboard);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

// Initialization routine.
void setup(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);

	// Create texture ids.
	glGenTextures(2, texture);

	// Load external texture.
	loadTextures();

	// Load internal texture.
	loadChessboardTexture();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

void drawAxis(float size){
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex3f(-size,0,0);
		glVertex3f(size,0,0);
	glEnd();

	glColor3f(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,-size,0);
		glVertex3f(0,size,0);
	glEnd();

	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,-size);
		glVertex3f(0,0,size);
	glEnd();
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Activate texture object.
	glBindTexture(GL_TEXTURE_2D, texture[id]);

	//------------------------------------------------------------
	glLoadIdentity();
	gluLookAt(15.0, 15.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	drawAxis(20);

	glRotatef(angle, 0.0, 1.0, 0.0);

	//------------------------------------------------------------
	// Map the texture onto a square polygon.
    glPolygonMode(GL_BACK,GL_LINE);
     glBegin(GL_POLYGON);
     glTexCoord2f(0.0, 0.0); glVertex3f(-10.0, -10.0, 0.0);
     glTexCoord2f(1.0, 0.0); glVertex3f(10.0, -10.0, 0.0);
     glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, 0.0);
     glTexCoord2f(0.0, 1.0); glVertex3f(-10.0, 10.0, 0.0);
     glEnd();

	//------------------------------------------------------------
	//Mapping a texture to a triangular surface
//     glBegin(GL_TRIANGLES);
//     glTexCoord2f(0.5, 1.0); glVertex3f(0,10,0);
//     glTexCoord2f(0.0, 0.0); glVertex3f(10,0,0);
//     glTexCoord2f(1.0, 0.0); glVertex3f(-10,0,0);
//     glEnd();

	//------------------------------------------------------------
	//Mapping a texture to a pyramid shape
	// glBegin(GL_TRIANGLES);
	// glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
	// glTexCoord2f(0.0, 0.0); glVertex3f(10,0,10);
	// glTexCoord2f(1.0, 0.0); glVertex3f(10,0,-10);
	//
	// glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
	// glTexCoord2f(1.0, 0.0); glVertex3f(10,0,-10);
	// glTexCoord2f(1.0, 1.0); glVertex3f(-10,0,-10);
	//
	// glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
	// glTexCoord2f(1.0, 1.0); glVertex3f(-10,0,-10);
	// glTexCoord2f(0.0, 1.0); glVertex3f(-10,0,10);
	//
	// glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
	// glTexCoord2f(0.0, 1.0); glVertex3f(-10,0,10);
	// glTexCoord2f(0.0, 0.0); glVertex3f(10,0,10);
	// glEnd();

	//-----------------------------------------------------------
	//Using multiple textures in the scene
//     glBegin(GL_TRIANGLES);
//     glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
//     glTexCoord2f(0.0, 0.0); glVertex3f(10,0,10);
//     glTexCoord2f(1.0, 0.0); glVertex3f(10,0,-10);
//
//     glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
//     glTexCoord2f(1.0, 0.0); glVertex3f(10,0,-10);
//     glTexCoord2f(1.0, 1.0); glVertex3f(-10,0,-10);
//     glEnd();
//
//     glBindTexture(GL_TEXTURE_2D, texture[1]);
//     glBegin(GL_TRIANGLES);
//     glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
//     glTexCoord2f(1.0, 1.0); glVertex3f(-10,0,-10);
//     glTexCoord2f(0.0, 1.0); glVertex3f(-10,0,10);
//
//     glTexCoord2f(0.5, 0.5); glVertex3f(0,10,0);
//     glTexCoord2f(0.0, 1.0); glVertex3f(-10,0,10);
//     glTexCoord2f(0.0, 0.0); glVertex3f(10,0,10);
//     glEnd();

	//------------------------------------------------------------

	//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//    float t=0;
//    glBegin(GL_TRIANGLE_STRIP);
//        for(int theta=0; theta<=180; theta+=10){
//            float x = cos(d2r(theta));
//            float y = sin(d2r(theta));
//
//            glTexCoord2f(0, t); glVertex3f(10*x,10*y,10);
//            glTexCoord2f(1, t); glVertex3f(10*x,10*y,-10);
//
//            t += 1.0/19;
//        }
//    glEnd();

	//------------------------------------------------------------
	//--- Repeating and Claming Ex
//     glBegin(GL_POLYGON);
//     glTexCoord2f(-1.0, -1.0); glVertex3f(-10.0, -10.0, 0.0);
//     glTexCoord2f(1.0, -1.0); glVertex3f(10.0, -10.0, 0.0);
//     glTexCoord2f(1.0, 1.0); glVertex3f(10.0, 10.0, 0.0);
//     glTexCoord2f(-1.0,1.0); glVertex3f(-10.0, 10.0, 0.0);
//     glEnd();

	glutSwapBuffers();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (float)w / (float)h, 1.0, 100.0);
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
	case ' ':
		id++;
		if (id == 2) id = 0;
		glutPostRedisplay();
		break;
	case 127:
		angle = 0.0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		angle -= 5.0;
		if (angle < 0.0) angle += 360.0;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		angle += 5.0;
		if (angle > 360.0) angle -= 360.0;
	}
	glutPostRedisplay();
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
	std::cout << "Interaction:" << std::endl;
	std::cout << "Press the left and right arrow keys to rotate the square." << std::endl
		<< "Press space to toggle between textures." << std::endl
		<< "Press delete to reset." << std::endl;
}

// Main routine.
int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("texturedSquare.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
