///////////////////////////////////
// square.cpp
//
// OpenGL program to draw a square.
//
// Sumanta Guha.
///////////////////////////////////

#include <GL/freeglut.h>

void writeBitmapString(void *font, const char *str){
	int i = 0;
	while(str[i] != '\0')
		glutBitmapCharacter(font, str[i++]);
}
void drawAxis(float size){
	glColor3f(1,0,0);
	glBegin(GL_LINES);
		glVertex3f(-size,0,0);
		glVertex3f(size,0,0);
	glEnd();

	glRasterPos3f(size, 0, 0.0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+X");

	glColor3f(0,1,0);
	glBegin(GL_LINES);
		glVertex3f(0,-size,0);
		glVertex3f(0,size,0);
	glEnd();

	glRasterPos3f(0, size, 0);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Y");

	glColor3f(0,0,1);
	glBegin(GL_LINES);
		glVertex3f(0,0,-size);
		glVertex3f(0,0,size);
	glEnd();

	glRasterPos3f(0, 0, size);
	writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Z");
}

//triangle corver vertices and colors
float vertices[3][3] = {{10,30,0},{90,50,0},{70,80,0}};
float colors[3][3] = {{1,0,0},{0,1,0},{0,0,1}};

//current vertex and its color
float v[3];
float c[3];

//This function determines the vertices (and their colors)
//that are inside the triangle using barycentric coordinates
//c1, c3, and c3
void findInsideVertexAndColor(float c1,float c2, float c3){
	v[0] = c1*vertices[0][0] + c2*vertices[1][0] + c3*vertices[2][0];
	v[1] = c1*vertices[0][1] + c2*vertices[1][1] + c3*vertices[2][1];
	v[2] = c1*vertices[0][2] + c2*vertices[1][2] + c3*vertices[2][2];

	c[0] = c1*colors[0][0] + c2*colors[1][0] + c3*colors[2][0];
	c[1] = c1*colors[0][1] + c2*colors[1][1] + c3*colors[2][1];
	c[2] = c1*colors[0][2] + c2*colors[1][2] + c3*colors[2][2];
}

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawAxis(90);

	//-------------------------------------------------
	//OpenGL Implementation
	// glBegin(GL_TRIANGLES);
	// 	glColor3f(1,0,0); glVertex3f(10,30,0);
	// 	glColor3f(0,1,0); glVertex3f(90,50,0);
	// 	glColor3f(0,0,1); glVertex3f(70,80,0);
	// glEnd();

	//-------------------------------------------------
	// My Implementation
	glBegin(GL_POINTS);
		float i = 1;
		while(i >= 0){
			float rem = 1 - i;
			float j = 0;
			while(j <= rem){
				float k = rem - j;
				//i,j,k are barycentric coordinates
				findInsideVertexAndColor(i,j,k);
				glColor3f(c[0],c[1],c[2]); glVertex3f(v[0],v[1],v[2]);

				j+=0.001;
			}
			i-=0.001;
		}
	glEnd();

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
	glOrtho(-10.0, 100.0, -10.0, 100.0, -1.0, 1.0);

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

// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out squareEx.cpp
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
