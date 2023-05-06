#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
/* MARK: movingCamera*/
//#define MSEC_PER_FRAME 10
//#define PI 3.14159265
//#define N 40.0 // Number of vertices on the boundary of the disc.
//
//int rot=0;
//bool pauseMotion = false;
//int switchView = 0;
//
//float d2r(int degree){return ((PI / 180.0) * degree);} //degree to radians
//
//void writeBitmapString(void* font, const char* string){
//    for (int i=0; string[i] != '\0'; i++)
//        glutBitmapCharacter(font, string[i]);
//}
//
//void drawAxis(float size){
//    glColor3f(1,0,0);
//    glBegin(GL_LINES);
//        glVertex3f(-size,0,0);
//        glVertex3f(size,0,0);
//    glEnd();
//
//    glRasterPos3f(size, 0, 0.0);
//    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+X");
//
//    glColor3f(0,1,0);
//    glBegin(GL_LINES);
//        glVertex3f(0,-size,0);
//        glVertex3f(0,size,0);
//    glEnd();
//
//    glRasterPos3f(0, size, 0);
//    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Y");
//
//    glColor3f(0,0,1);
//    glBegin(GL_LINES);
//        glVertex3f(0,0,-size);
//        glVertex3f(0,0,size);
//    glEnd();
//
//    glRasterPos3f(0, 0, size);
//    writeBitmapString(GLUT_BITMAP_HELVETICA_18, "+Z");
//}
//
//void drawDisc(float R, float X, float Y, float Z, bool dash){
//
//    if(dash) glBegin(GL_LINES);
//    else glBegin(GL_LINE_STRIP);
//        for (int i = 0; i <= N; ++i){
//            float t = 2 * PI * i / N;
//            glVertex3f(X + cos(t) * R, Y, Z + sin(t) * R);
//        }
//    glEnd();
//}
//void drawRandomObjects(){
//    int p = 17;
//    glPushMatrix();
//        glScalef(1,3,1);
//        glPushMatrix();
//            glTranslatef(p,1,0);
//            glColor3f(0,0,0); glutWireCube(2);
//            glColor3f(0,1,0); glutSolidCube(2);
//        glPopMatrix();
//        glPushMatrix();
//            glTranslatef(-p,1,0);
//            glColor3f(0,0,0); glutWireCube(2);
//            glColor3f(0,0,1); glutSolidCube(2);
//        glPopMatrix();
//        glPushMatrix();
//            glTranslatef(0,1,-p);
//            glColor3f(0,0,0); glutWireCube(2);
//            glColor3f(0,1,1); glutSolidCube(2);
//        glPopMatrix();
//        glPushMatrix();
//            glTranslatef(0,1,p);
//            glColor3f(0,0,0); glutWireCube(2);
//            glColor3f(1,0,0); glutSolidCube(2);
//        glPopMatrix();
//    glPopMatrix();
//}
//void drawCar(){
//    glPushMatrix();
//        glTranslatef(0, 1, -2);
//        glScalef(2,1,1);
//        glColor3f(0,0,0);glutWireCube(2);
//        glColor3f(1,0,1);glutSolidCube(2);
//    glPopMatrix();
//    glPushMatrix();
//        glTranslatef(0, 2, 1);
//        glColor3f(0,0,0);glutWireCube(4);
//        glColor3f(1,0,1);glutSolidCube(4);
//    glPopMatrix();
//}
//void drawRoad(){
//    glPushMatrix();
//        glColor3f(0,0,0);
//        drawDisc(10,0,0,0,false);
//        drawDisc(16,0,0,0,false);
//        drawDisc(13,0,0,0,true);
//    glPopMatrix();
//}
//
//// Drawing routine.
//void drawScene(void){
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glEnable(GL_DEPTH_TEST);
//    //------------------------------------------------
//    glLoadIdentity();
//    //gluLookAt(10,15,25,0,0,0,0,1,0);
//    float p1[] = {13,5,0}; //eye position
//    float p2[] = {13,5,-1}; //center position
//    gluLookAt(p1[0]*cos(d2r(rot))+p1[2]*sin(d2r(rot)),
//              p1[1],
//                     -p1[0]*sin(d2r(rot))+p1[2]*cos(d2r(rot)),
//                        p2[0]*cos(d2r(rot))+p2[2]*sin(d2r(rot)),
//                        p2[1],
//                     -p2[0]*sin(d2r(rot))+p2[2]*cos(d2r(rot)),
//                        0, 1, 0);
//    //------------------------------------------------
//    drawAxis(20);
//    drawRoad();
//    drawRandomObjects();
//
//    glPushMatrix();
//        glRotatef(rot,0,1,0);
//        glTranslatef(13,0,0);
//        drawCar();
//    glPopMatrix();
//    //------------------------------------------------
//    glDisable(GL_DEPTH_TEST);
//    glFlush();
//}
//
//// Keyboard input processing routine.
//void keyInput(unsigned char key, int x, int y){
//    switch (key)
//    {
//        case 27:
//            exit(0);
//            break;
//        case ' ':
//            if(pauseMotion) pauseMotion = false;
//            else pauseMotion = true;
//            break;
//        case 's':
//            switchView = (switchView+1)%2;
//            break;
//        default:
//            break;
//    }
//}
//
////Timer function is called in every MSEC_PER_FRAME milliseconds
//void timerFunc(int value){
//
//    if(!pauseMotion) rot = (rot+1)%360;
//
//    glutPostRedisplay();
//    glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
//}
//
//// Initialization routine.
//void setup(void){
//    glClearColor(1.0, 1.0, 1.0, 0.0);
//}
//
//// OpenGL window reshape routine.
//void resize(int w, int h){
//    glViewport(0, 0, w, h);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glFrustum(-5.0, 5.0, -5.0, 5.0, 5, 100);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//// Main routine.
//int main(int argc, char **argv){
//    srand(time(0));
//
//    glutInit(&argc, argv);
//
//    glutInitContextVersion(4, 3);
//    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
//
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
//    glutInitWindowSize(500, 500);
//    glutInitWindowPosition(100, 100);
//    glutCreateWindow("Modelview Transformation Example");
//    glutDisplayFunc(drawScene);
//    glutReshapeFunc(resize);
//    glutKeyboardFunc(keyInput);
//
//    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);
//
//    glewExperimental = GL_TRUE;
//    glewInit();
//
//    setup();
//
//    glutMainLoop();
//}


/* MARK: obj balls collision*/
/*
using namespace std;

#define MSEC_PER_FRAME 10
#define NUMBER_OF_BALLS 5

#define NO_WALL_COLLISION 0
#define LEFT_WALL 1
#define RIGHT_WALL 2
#define TOP_WALL 3
#define BOTTOM_WALL 4

bool pauseGame = false;

class ball {
    public:
        float _x;
        float _y;
        float _z;
        float _vx;
        float _vy;
        float _vz;
        float _radius;
        float* _color;

    public:
        ball(){}
        ball(float x, float y, float vx,float vy,float r) {
            _x = x; _y = y; _z = 0;
            _vx = vx; _vy = vy; _vz = 0;
            _radius = r;
        }

        void move() {
            _x += _vx;
            _y += _vy;
        }

        int checkWallCollision() {
            if (_x >= 500 - _radius)
                return RIGHT_WALL;
            else if (_x <= 0 + _radius)
                return LEFT_WALL;
            else if (_y >= 500 - _radius)
                return TOP_WALL;
            else if (_y <= 0 + _radius)
                return BOTTOM_WALL;
            else
                return NO_WALL_COLLISION;
        }

        bool checkObjCollision(ball b) {
            float r = _radius + b._radius;
            float distSq = ((_x - b._x) * (_x - b._x)) +
                            ((_y - b._y) * (_y - b._y)) +
                            ((_z - b._z) * (_z - b._z));

            if (r * r >= distSq)
                return true;
            else
                return false;
        }

};

ball ballArray[NUMBER_OF_BALLS];

void constructAllBalls() {
    for (int i = 0; i < NUMBER_OF_BALLS; i++) {
        ballArray[i]._x = rand() % 400 + 50;
        ballArray[i]._y = rand() % 400 + 50;
        ballArray[i]._z = 0;
        ballArray[i]._vx = rand() % 8 - 4;
        ballArray[i]._vy = rand() % 8 - 4;
        ballArray[i]._vz = 0;
        ballArray[i]._radius = rand()%20+10;
        ballArray[i]._color = new float[3];
        ballArray[i]._color[0] = 1.0 / ((rand() % 10) + 1);
        ballArray[i]._color[1] = 1.0 / ((rand() % 10) + 1);
        ballArray[i]._color[2] = 1.0 / ((rand() % 10) + 1);
    }
}

void handleCollision(ball &b1, ball &b2) {
    float tmp = b1._vx;
    b1._vx = b2._vx;
    b2._vx = tmp;

    tmp = b1._vy;
    b1._vy = b2._vy;
    b2._vy = tmp;
}

// Drawing routine.
void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    //------------------------------------------------
    glLoadIdentity();

    for (int i = 0; i < NUMBER_OF_BALLS; i++) {
        glColor3fv(ballArray[i]._color);
        glPushMatrix();
        glTranslatef(ballArray[i]._x, ballArray[i]._y, ballArray[i]._z);
        glScalef(ballArray[i]._radius, ballArray[i]._radius, 1);
        glutSolidSphere(1, 100, 100);
        glPopMatrix();
    }

    //-------------------------------------------------
    glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y) {
    switch (key)
    {
    case 27:
        exit(0);
        break;
    case ' ':
        pauseGame = (pauseGame + 1) % 2;
    default:
        break;
    }
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value) {

    if (!pauseGame) {
        for (int i = 0; i < NUMBER_OF_BALLS; i++) {

            ballArray[i].move();

            int wall = ballArray[i].checkWallCollision();
            if (wall == LEFT_WALL || wall == RIGHT_WALL)
                ballArray[i]._vx *= -1;
            else if (wall == TOP_WALL || wall == BOTTOM_WALL)
                ballArray[i]._vy *= -1;

            for (int j = i + 1; j < NUMBER_OF_BALLS; j++) {
                bool objCol = ballArray[i].checkObjCollision(ballArray[j]);
                if (objCol)
                    handleCollision(ballArray[i], ballArray[j]);
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(MSEC_PER_FRAME, timerFunc, value);
}

// Initialization routine.
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -100, 100);
    //gluPerspective(90.0, 1, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main routine.
int main(int argc, char** argv) {
    srand(time(0));
    constructAllBalls();

    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Object Collision Example 1 (AXIS-ALIGNED)");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}*/

/* MARK: objectCollison_AABB*/
/*#define MSEC_PER_FRAME 10

//Here we are defining two axis-aligned rectangular objects
//object 1 is stationary and object 2 is moving from different directions
//checkCollision() function can detect all collisions!

float obj1[] = {250,250,0};
float obj1SizeX = 40;
float obj1SizeY = 40;

float obj2[] = {400,110,0};
float obj2SizeX = 20;
float obj2SizeY = 20;

bool objCollision = false;
bool pauseGame = false;

void writeBitmapString(void *font, char *string){
    for (char* c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

void drawEndGameMessage(char* msg){

    glPushMatrix();
        glLoadIdentity();
        glTranslatef(250,350,0);
        glScalef(2,1,1);
        glColor3f(1,0,0);glutSolidCube(100);
    glPopMatrix();

    glColor3f(1,1,1);
    glWindowPos3f(170, 350, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, msg);
}

// Drawing routine.
void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT);

    //------------------------------------------------
    glLoadIdentity();

    glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(obj1[0],obj1[1],obj1[2]);
    glScalef(obj1SizeX,obj1SizeY,1);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0,1,0);
    glTranslatef(obj2[0],obj2[1],obj2[2]);
    glScalef(obj2SizeX,obj2SizeY,1);
    glutSolidCube(1);
    glPopMatrix();

    if(objCollision)
        drawEndGameMessage("Collision!");

    //-------------------------------------------------
    glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 'a':
            obj2[0]-=40;
            break;
        case 'd':
            obj2[0]+=40;
            break;
        default:
            break;
    }
}

bool checkCollision(){
    if(obj1[0]-obj1SizeX/2 <= obj2[0]+obj2SizeX/2 &&
         obj1[0]+obj1SizeX/2 >= obj2[0]-obj2SizeX/2 &&
     obj1[1]-obj1SizeY/2 <= obj2[1]+obj2SizeY/2 &&
         obj1[1]+obj1SizeY/2 >= obj2[1]-obj2SizeY/2)
    return true;
    else
        return false;
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){

    //object 2 is moving towards object 1 from different directions
    if(!pauseGame){
        obj2[1]++;
        obj2[0]--;
        objCollision = checkCollision();
    }

    if(objCollision)
        pauseGame = true;

    glutPostRedisplay();
    glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
}

// Initialization routine.
void setup(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h){
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Main routine.
int main(int argc, char **argv){
    srand(time(0));

    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Object Collision Example 1 (AXIS-ALIGNED)");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}*/

/* MARK: objectCollisionEx2 */
/*#define MSEC_PER_FRAME 10
#define PI 3.14159265
#define N 40.0 // Number of vertices on the boundary of the disc.

int rotCar = 0; //Car's current rotation angle.
int rotObj = 0; //Random rotation angle of the object

bool pauseGame = false;
bool objVisible = false;
bool objCollision = false;

float obj[4] = {13, 2, 0};
float car[4] = {13, 2, 0};

float d2r(int degree){return ((PI / 180.0) * degree);} //degree to radians

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

void drawDisc(float R, float X, float Y, float Z, bool dash){
    if(dash) glBegin(GL_LINES);
    else glBegin(GL_LINE_STRIP);
        for (int i = 0; i <= N; ++i){
            float t = 2 * PI * i / N;
            glVertex3f(X + cos(t) * R, Y, Z + sin(t) * R);
        }
    glEnd();
}
void drawRandomObjects(){
    int p = 17;
    glPushMatrix();
        glScalef(1,3,1);
        glPushMatrix();
            glTranslatef(p,1,0);
            glColor3f(0,0,0); glutWireCube(2);
            glColor3f(0,1,0); glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-p,1,0);
            glColor3f(0,0,0); glutWireCube(2);
            glColor3f(0,0,1); glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,1,-p);
            glColor3f(0,0,0); glutWireCube(2);
            glColor3f(0,1,1); glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,1,p);
            glColor3f(0,0,0); glutWireCube(2);
            glColor3f(1,0,0); glutSolidCube(2);
        glPopMatrix();
    glPopMatrix();
}
void drawCar(){
    glPushMatrix();
        glRotatef(rotCar,0,1,0);
        glTranslatef(car[0],0,car[2]);
        glPushMatrix();
            glTranslatef(0, car[1]/2, -2);
            glScalef(2,1,1);
            glColor3f(0,0,0);glutWireCube(2);
            glColor3f(1,0,1);glutSolidCube(2);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, car[1], 1);
            glColor3f(0,0,0);glutWireCube(4);
            glColor3f(1,0,1);glutSolidCube(4);
        glPopMatrix();
    glPopMatrix();
}
void drawRoad(){
    glPushMatrix();
        glColor3f(0,0,0);
        drawDisc(10,0,0,0,false);
        drawDisc(16,0,0,0,false);
        drawDisc(13,0,0,0,true);
    glPopMatrix();
}

void drawObstacleObject(){
    glPushMatrix();
        glRotatef(rotObj,0,1,0);
        glTranslatef(obj[0],obj[1],obj[2]);
        glColor3f(0,0,0); glutWireCube(3);
        glColor3f(0.5,0.5,0.5); glutSolidCube(3);
    glPopMatrix();
}

void drawEndGameMessage(char* msg){
    glPushMatrix();
        glLoadIdentity();
        glTranslatef(0,0,-6);
        glScalef(2,1,1);
        glColor3f(1,0,0);glutSolidCube(2);
    glPopMatrix();

    glColor3f(1,1,1);
    glWindowPos3f(170, 250, 0);
    writeBitmapString(GLUT_BITMAP_HELVETICA_18, msg);
}

// Drawing routine.
void drawScene(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    //------------------------------------------------
    glLoadIdentity();
    gluLookAt(10,15,25,0,0,0,0,1,0);

    //------------------------------------------------
    drawAxis(20);
    drawRoad();
    drawRandomObjects();
    drawCar();

    if(objVisible)
        drawObstacleObject();
    else{
        glColor3f(0,0,0);
        glWindowPos3f(100, 20, 0);
        writeBitmapString(GLUT_BITMAP_HELVETICA_18, "Press 'o' to spawn random object.");
    }

    if(objCollision)
        drawEndGameMessage("Collision! (R)etry?");

    //-------------------------------------------------
    glDisable(GL_DEPTH_TEST);
    glFlush();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y){
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case ' ':
            pauseGame = (pauseGame+1)%2;
            break;
        case 'r':
            objVisible = false;
            objCollision = false;
            pauseGame = false;
            break;
        case 'o':
            if(!objCollision){
                objVisible = (objVisible+1)%2;
                rotObj = (rand() % 360);
            }
            break;
        default:
            break;
    }
}

bool checkCollision(){
    float cx = car[0]*cos(d2r(rotCar))+car[2]*sin(d2r(rotCar));
    float cy = car[1];
    float cz = -car[0]*sin(d2r(rotCar))+car[2]*cos(d2r(rotCar));

    float ox = obj[0]*cos(d2r(rotObj))+obj[2]*sin(d2r(rotObj));
    float oy = obj[1];
    float oz = -obj[0]*sin(d2r(rotObj))+obj[2]*cos(d2r(rotObj));

    float rCar = 3; //~3.60
    float rObj = 2; //~2.12

    float r = rCar + rObj;
    float distSq = ((cx-ox)*(cx-ox))+((cy-oy)*(cy-oy))+((cz-oz)*(cz-oz));

    if(r*r > distSq)
        return true;
    else
        return false;
}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){

    if(!pauseGame)
        rotCar = (rotCar+1)%360;

    if(objVisible)
        objCollision = checkCollision();

    if(objCollision)
        pauseGame = true;

    glutPostRedisplay();
    glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
}

// Initialization routine.
void setup(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h){
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5, 100);
    glMatrixMode(GL_MODELVIEW);
}

// Main routine.
int main(int argc, char **argv){
    srand(time(0));

    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Object Collision Example 2");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}*/

/* MARK: MOVING CUBES 3D*/
#define MSEC_PER_FRAME 10

int rotZ = 0;
bool pauseMotion = false;

float xCam = 10, yCam = 10, zCam = 20;

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

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glLoadIdentity();
    gluLookAt(xCam,yCam,zCam,0,0,-10,0,1,0);
    drawAxis(20);

    //------------------------------------------------
    glPushMatrix();
        glRotatef(rotZ,0,0,1);
        glColor3f(0,0,0); glutWireCube(5);
        glColor3f(1,0,0); glutSolidCube(5);
    glPopMatrix();

    //------------------------------------------------
    glPushMatrix();
        glTranslatef(15,15,0);
        glRotatef(rotZ,0,0,1);
        glColor3f(0,0,0); glutWireCube(5);
        glColor3f(1,0,1); glutSolidCube(5);
    glPopMatrix();

    //------------------------------------------------
    glPushMatrix();
        glRotatef(rotZ,0,0,1);
        glTranslatef(10,10,0);
        glColor3f(0,0,0); glutWireCube(5);
        glColor3f(0,0,1); glutSolidCube(5);
    glPopMatrix();

    //------------------------------------------------
    glPushMatrix();
        glRotatef(rotZ,0,0,1);
        glTranslatef(5,5,0);
        glRotatef(-rotZ,0,0,1);
        glColor3f(0,0,0); glutWireCube(5);
        glColor3f(0,1,1); glutSolidCube(5);
    glPopMatrix();
    //------------------------------------------------
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

// Initialization routine.
void setup(void){
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(90,w/h,5,100);
    
    //glOrtho(-25,25,-25,25,-5,100);

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
            if(pauseMotion) pauseMotion = false;
            else pauseMotion = true;
            break;
        case 'a':
            xCam-=0.5;
            break;
        case 'd':
            xCam+=0.5;
            break;
        case 'w':
            yCam+=0.5;
            break;
        case 's':
            yCam-=0.5;
            break;
        case 'u':
            zCam-=0.5;
            break;
        case 'j':
            zCam+=0.5;
            break;
        default:
            break;
    }
    //std::cout << x << " " << y << " " << z << std::endl;

}

//Timer function is called in every MSEC_PER_FRAME milliseconds
void timerFunc(int value){
    if(!pauseMotion)
        rotZ = (rotZ+1)%360;

  glutPostRedisplay();
  glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Modelview Transformation Example");
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);

    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}
