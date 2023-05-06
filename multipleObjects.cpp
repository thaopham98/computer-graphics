#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h>

using namespace std;

//Turn light ON and OFF
bool light0_ON = GL_TRUE;

//Light and object position
float light0Pos[] = {0, 10, 10, 1};
float objectPos[] = {0,  0,  0};

// Light property vectors.
float lightAmbient[] = { 0.0, 0.0, 0.0, 1.0 }; //Ambient
float lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };	//Diffuse
float lightSpecular[]= { 1.0, 1.0, 1.0, 1.0 }; //Specular
float globAmbient[]  = { 0.2, 0.2, 0.2, 1.0 }; //Global Ambient

// Material property vectors.
float matAmbient[]  = { 0.0, 1.0, 0.0, 1.0 }; //Ambient Reflectance
float matDiffuse[]  = { 0.0, 1.0, 0.0, 1.0 }; //Diffuse Reflectance
float matSpecular[] = { 1.0, 1.0, 1.0, 1.0 }; //Specular Reflectance
float matShininess[]= { 20 };	//Shininess factor
float matEmission[] = { 0.0, 0.0, 0.0, 1.0 }; //Object Light Emission

//Some utility functions!
void writeBitmapString(void *font, char *string){
	for (char* c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
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
void drawLightSource(bool on){
	if(on){
		glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(light0Pos[0],light0Pos[1],light0Pos[2]);
		glutSolidSphere(0.2,20,20);
		glPopMatrix();
	}
}
void writeData(){

	if(light0_ON) cout << "[  l  ] Light is ON" << endl;
	else cout << "[  l  ] Light is OFF" << endl;

	if(light0Pos[3] == 1) cout << "[  p  ] Positional Light is ON" << endl;
	else cout << "[  p  ] Directional Light is ON" << endl;

	cout << "[Arrow] Light Position  : (";
	cout << light0Pos[0] << ","
			 << light0Pos[1] << ","
			 << light0Pos[2] << ")" << endl;

	cout << "[WASD ] Object Position : (";
 	cout << objectPos[0] << ","
 			 << objectPos[1] << ","
 			 << objectPos[2] << ")" << endl;

	cout << "[ k/K ] Ambient Light   : (";
	cout << lightAmbient[0] << ","
			 << lightAmbient[1] << ","
			 << lightAmbient[2] << ")" << endl;

	cout << "[ j/J ] Diffuse Light   : (";
 	cout << lightDiffuse[0] << ","
 			 << lightDiffuse[1] << ","
 			 << lightDiffuse[2] << ")" << endl;

	cout << "[ h/H ] Specular Light  : (";
 	cout << lightSpecular[0] << ","
 			 << lightSpecular[1] << ","
 			 << lightSpecular[2] << ")" << endl;

	cout << "[ n/N ] Shininess Value : (";
	cout << matShininess[0] << ")" << endl;
	cout << "--------------------------------\n" << endl;
}

// Initialization routine.
void setup(void){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST); // Enable depth testing.

	// Cull back faces.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void setLightProperties(){
	// Light0 properties.
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,lightSpecular);

	// Global ambient light, applied to all lights
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmbient);

	//set the position of light
	glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);

	if(light0_ON)	glEnable(GL_LIGHT0);
	else glDisable(GL_LIGHT0);
}
void setObjMaterialProperties(){
	// Material properties of ball.
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, matEmission);

	/*
	There is only one object here.
	If there are multiple objects having different properties,
	these parameters must be set.
	*/
}

void setMultipleObjectProperties(){
	// Material properties shared by all the spheres.
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

	// Enable color material mode:
	// The ambient and diffuse color of the front faces will track the color set by glColor().
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//This way, we do not need to create arrays for
	//ambient and diffuse material properties. OpenGL
	//will use glColor() inputs as ambient and diffuse
	//material properties.
}

void drawScene(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(10.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	drawAxis(20);
	drawLightSource(light0_ON);
	writeData();
	//---------------------------------

	glEnable(GL_LIGHTING);
		setLightProperties();

		//setObjMaterialProperties();
		setMultipleObjectProperties();

		glPushMatrix();
		glColor4f(1,0,0,1);
		glTranslatef(objectPos[0]-5, objectPos[1]-5, objectPos[2]);
		glutSolidSphere(4,200,200);
		glPopMatrix();

		glPushMatrix();
		glColor4f(0,1,0,1);
		glTranslatef(objectPos[0]+5, objectPos[1]-5, objectPos[2]);
		glutSolidSphere(4,200,200);
		glPopMatrix();

		//next two objects are not reflecting specular light
		float newSpec[] = {0,0,0,1};
		glMaterialfv(GL_FRONT, GL_SPECULAR, newSpec);

		glPushMatrix();
		glColor4f(0,1,1,1);
		glTranslatef(objectPos[0]+5, objectPos[1]+5, objectPos[2]);
		glutSolidSphere(4,200,200);
		glPopMatrix();

		glPushMatrix();
		glColor4f(1,1,0,1);
		glTranslatef(objectPos[0]-5, objectPos[1]+5, objectPos[2]);
		glutSolidSphere(4,200,200);
		glPopMatrix();

	glDisable(GL_LIGHTING);

	//---------------------------------
	glutSwapBuffers();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'w':
		objectPos[1]++;
		break;
	case 's':
		objectPos[1]--;
		break;
	case 'a':
		objectPos[0]--;
		break;
	case 'd':
		objectPos[0]++;
		break;
	case 'l':
		light0_ON = !light0_ON;
		break;
	case 'p':
		if (light0Pos[3] == 0) light0Pos[3] = 1;
		else light0Pos[3] = 0;
		break;
	case 'h':
			lightSpecular[0] -= 0.1;
			lightSpecular[1] -= 0.1;
			lightSpecular[2] -= 0.1;
			break;
	case 'H':
			lightSpecular[0] += 0.1;
			lightSpecular[1] += 0.1;
			lightSpecular[2] += 0.1;
			break;
	case 'j':
			lightDiffuse[0] -= 0.1;
			lightDiffuse[1] -= 0.1;
			lightDiffuse[2] -= 0.1;
			break;
	case 'J':
			lightDiffuse[0] += 0.1;
			lightDiffuse[1] += 0.1;
			lightDiffuse[2] += 0.1;
			break;
	case 'k':
			lightAmbient[0] -= 0.1;
			lightAmbient[1] -= 0.1;
			lightAmbient[2] -= 0.1;
			break;
	case 'K':
			lightAmbient[0] += 0.1;
			lightAmbient[1] += 0.1;
			lightAmbient[2] += 0.1;
			break;
	case 'n':
			matShininess[0] -= 1;
			break;
	case 'N':
			matShininess[0] += 1;
			break;
	default:
		break;
	}
	glutPostRedisplay();
}

// Callback routine for non-ASCII key entry.
void specialKeyInput(int key, int x, int y){
	switch (key) {
		case GLUT_KEY_UP:
			light0Pos[1]++;
			break;
		case GLUT_KEY_DOWN:
			light0Pos[1]--;
			break;
		case GLUT_KEY_LEFT:
			light0Pos[0]--;
			break;
		case GLUT_KEY_RIGHT:
			light0Pos[0]++;
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

// OpenGL window reshape routine.
void resize(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, (float)w / (float)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv){
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("lightAndMaterial1.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutSpecialFunc(specialKeyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}
