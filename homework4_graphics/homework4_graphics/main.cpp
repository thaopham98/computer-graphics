#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>

#define MSEC_PER_FRAME 20

using namespace std;

/* MARK: class obstacle */
class obstacle{
public:
    float x;
    float y;
    float z;
    obstacle(){}; //Constructor
};

bool objCollision = false; // not detecting
bool pauseGame = false; // moving != (pauseGame = Not moving)
bool visibleObstacles = false; // invisible
bool boostItem = true; // detecting

int size;

float objCar[] = {3, 1, 505};
float objCarX = .5;
float objCarY = .5;
float objCarZ = .5;

float eyeZ = 520;
float centerZ = 1;

float msgLocation = 500;

obstacle leftObstacles[10]; // storing 10 obstacles on the left
float leftObstaclesSizeX = 1;
float leftObstaclesSizeY = 1;
float leftObstaclesSizeZ = 1;

obstacle rightObstacles[10]; // storing 10 obstacles on the right
float rightobstablesSizeX = 1;
float rightobstablesSizeY = 1;
float rightobstablesSizeZ = 1;

obstacle boostItems[3]; // storing 3 boosting items
float boostItemsSizeX = 1;
float boostItemsSizeY = 1;
float boostItemsSizeZ = 1;

/* MARK: Messages */
void writeBitmapString(void *font, char *string)
{
    for (char* c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}
// Routine to write object name.
void writeWinMessage()
{
    glColor3f(1, 0, 0);
    glRasterPos3f(-8, 17, -500);
    writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "You Win! Congratulations!");
}
void writeStartMessage()
{
    glColor3f(1, 0, 0);
    glRasterPos3f(-9, 22, 501);
    writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Press \'s\' to start the game");
}
void SPACEMessage(){
    glColor3f(0, 0, 0);
    glRasterPos3f(-5.5, 27, msgLocation);
    writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Press SPACE to pause/continue");
}
void arrowMessage(){
    glColor3f(0, 0, 0);
    glRasterPos3f(-5, 25, msgLocation);
    writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Left/Right key to move the car");
}
void endGame(){
    glColor3f(1, 0, 0);
    glRasterPos3f(-3.5, 20, msgLocation);
    writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "You lose!");
}
void restartMessage(){
    glColor3f(0, 1, 0);
    glRasterPos3f(-10, 17, msgLocation);
    writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, "Press \'r\' to restart the game");
}
void alertScore(char* msg){ /*Showing score*/
    glPushMatrix();
        glColor3f(0.5, 0.0, 0.5);
        glRasterPos3f(-19, 27, msgLocation);
        writeBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, msg);
    glPopMatrix();
}
/* MARK: Shape's Functions */
void road(float size){ //   Road
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex3f(-8, 0, -size);
    glVertex3f(8, 0, -size);
    glVertex3f(8, 0, size);
    glVertex3f(-8, 0, size);
    glEnd();
}
void drawCar(){ //  Car
    glPushMatrix();
        glTranslatef(0, 0, -1);
        glScalef(2,1,1);
        glColor3f(0,0,0);glutWireCube(2);
        glColor3f(1,0,1);glutSolidCube(2);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0, 1, 1);
        glColor3f(0,0,0);glutWireCube(4);
        glColor3f(1,0,1);glutSolidCube(4);
    glPopMatrix();
}
void randomObstacle(){ //   Random Obstacles
    /*Right obstacles*/
    for (int j = 0; j < 10; j++)
    {
        glPushMatrix();
        glTranslatef(rightObstacles[j].x, rightObstacles[j].y, rightObstacles[j].z);
        glScalef(rightobstablesSizeX, rightobstablesSizeY, rightobstablesSizeZ);
        glColor3f(0, 0, 0);glutWireCube(1);
        glColor3f(1, 0, 0);glutSolidCube(1);
        glPopMatrix();
    }
    /*Left obtacles*/
    for (int i = 0; i < 10; i++)
    {
        glPushMatrix();
        glTranslatef(leftObstacles[i].x, leftObstacles[i].y, leftObstacles[i].z);
        glScalef(leftObstaclesSizeX, leftObstaclesSizeY, leftObstaclesSizeZ);
        glColor3f(0, 0, 0);glutWireCube(1);
        glColor3f(1, 0, 0);glutSolidCube(1);
        glPopMatrix();
    }
}

void randomItem(){ // Random Boosting Items
    for (int i = 0; i < 1; i++)
    {
        glPushMatrix();
        glTranslatef(boostItems[i].x, boostItems[i].y, boostItems[i].z);
        glScalef(boostItemsSizeX, boostItemsSizeY, boostItemsSizeZ);
        glColor3f(0, 0, 0);glutWireCube(1);
        glColor3f(0, 0, 1);glutSolidCube(1);
        glPopMatrix();
    }
}

/* MARK: checkCollision()*/
bool checkCollision(){/*----- AABB Collision -----*/
    for (int i = 0; i<10; i++)
    {
        if((leftObstacles[i].x-leftObstaclesSizeX/2 <= objCar[0]+objCarX/2 && leftObstacles[i].x+leftObstaclesSizeX/2 >= objCar[0]-objCarX/2 && leftObstacles[i].y-leftObstaclesSizeY/2 <= objCar[1]+objCarY/2 && leftObstacles[i].y+leftObstaclesSizeY/2 >= objCar[1]-objCarY/2 && leftObstacles[i].z-leftObstaclesSizeZ/2 <= objCar[2]+objCarZ/2 && leftObstacles[i].z+leftObstaclesSizeZ/2 >= objCar[2]-objCarZ/2) || (rightObstacles[i].x-rightobstablesSizeX/2 <= objCar[0]+objCarX/2 && rightObstacles[i].x+rightobstablesSizeX/2 >= objCar[0]-objCarX/2 && rightObstacles[i].y-rightobstablesSizeY/2 <= objCar[1]+objCarY/2 && rightObstacles[i].y+rightobstablesSizeY/2 >= objCar[1]-objCarY/2 && rightObstacles[i].z-rightobstablesSizeZ/2 <= objCar[2]+objCarZ/2 && rightObstacles[i].z+rightobstablesSizeZ/2 >= objCar[2]-objCarZ/2))
            return true;
        
    }
    return false;
}

bool boostItems_collision()
{
    for(int i = 0; i<3; i++)
    {
        if(boostItems[i].x-boostItemsSizeX/2 <= objCar[0]+objCarX/2 && boostItems[i].x+boostItemsSizeX/2 >= objCar[0]-objCarX/2 && boostItems[i].y-boostItemsSizeX/2 <= objCar[1]+objCarY/2 && boostItems[i].y+boostItemsSizeX/2 >= objCar[1]-objCarY/2 && boostItems[i].z-boostItemsSizeX/2 <= objCar[2]+objCarZ/2 && boostItems[i].z+boostItemsSizeX/2 >= objCar[2]-objCarZ/2)
            return true;
    }
    return false;
}

/* MARK: Drawing routine */
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    glLoadIdentity();
//    gluLookAt(0, 20, -530, 0, 1, 0, 0, 1, 0); // Eye position at the finish line
//    gluLookAt(0, 20, 530, 0, 1, 0, 0, 1, 0);  // Eye position at the start line
//    gluLookAt(0, 10, eyeZ, 0, 0, -500 , 0, 1, 0); // Looking at the finish line
    gluLookAt(0, 10, eyeZ, 0, 0, centerZ , 0, 1, 0);
    
    road(500);

    glPushMatrix();
        glTranslatef(objCar[0],objCar[1],objCar[2]);
        glScalef(objCarX, objCarY, objCarZ);
        drawCar();
    glPopMatrix();
    
    if(visibleObstacles) //Displaying the obstacles and boosting items on the road
    {
        randomObstacle();
        randomItem();
    }
    
    if (objCar[2] > 400)
        alertScore("Score: 0 point");
    else if (objCar[2] <= 400 && objCar[2] >= 301)
        alertScore("Score: 10 points");
    else if (objCar[2] <= 300 && objCar[2] >= 201)
        alertScore("Score: 20 points");
    else if (objCar[2] <= 200 && objCar[2] >= 101)
        alertScore("Score: 30 points");
    else if (objCar[2] <= 100 && objCar[2] >= 1)
        alertScore("Score: 40 points");
    else if (objCar[2] <= 0 && objCar[2] >= -99)
        alertScore("Score: 50 points");
    else if (objCar[2] <= -100 && objCar[2] >= -199)
        alertScore("Score: 60 points");
    else if (objCar[2] <= -200 && objCar[2] >= -299)
        alertScore("Score: 70 points");
    else if (objCar[2] <= -300 && objCar[2] >= -399)
        alertScore("Score: 80 points");
    else if (objCar[2] <= -400 && objCar[2] >= -499)
        alertScore("Score: 90 points");
    else if (objCar[2] < -500)
        alertScore("Score: 100 points");
    
    if (objCar[2]<-500) /* Win Message*/
        writeWinMessage();
    else if (objCar[2]>500) /* Start Message */
    {   writeStartMessage();
        SPACEMessage();
        arrowMessage();
    }
    else /* During play */
    {
        arrowMessage();
        SPACEMessage();
    }
    
    if(objCollision){
        endGame();
        restartMessage();
    }
    
    glDisable(GL_DEPTH_TEST);
    glFlush();
}
/* MARK: timerFunc */
void timerFunc(int value){
    boostItem = boostItems_collision();
    if (objCar[2]<-500) /* WIN and car stop moving */
        pauseGame = true;
    
    if (objCar[2]>500) /* Starting line */
        pauseGame = true;
    else if (500 <= objCar[2] && objCar[2] <= -500)
    {
        pauseGame = false;
        cout << "+++\'s\' is pressed. car is moving";
    }

    if(!pauseGame){ // For SPACE KEY: true = moving = car is running
        objCar[2]--; //Car is moving from +Z to -Z
        eyeZ--;
        centerZ--;
        msgLocation--;
        boostItem = boostItems_collision(); // false
        objCollision = checkCollision(); // by default is false == car moving
    }
    else
    {
        pauseGame = true;
//        cout << "\nCar's not moving\n";
    }
    
    if(objCollision == true)
    {
        pauseGame = true; // Stop the Game
    }

    glutPostRedisplay();
    glutTimerFunc (MSEC_PER_FRAME, timerFunc, value);
}
/* MARK: keyInput Function */
void keyInput(unsigned char key, int x, int y){
    switch (key)
    {
        case 27:
            exit(0);
            break;
        case 's': /* Press 's' to start the game */
//            cout << "\n+++\'s\' is pressed.\n";
            objCar[2]= 500; // car location
            pauseGame = false; //Car starts to move
            visibleObstacles = true; // The obstacles become visible
            
            for (int i = 0; i < 10; i++){ //Getting random numbers for left obstacles on z-axis
                leftObstacles[i].x = -3;
                leftObstacles[i].y = 1;
                leftObstacles[i].z = rand()%1000 + -500;
//                cout << "\nrandom numbers for LEFT obstacles on z-axis: " << leftObstacles[i].z << '\n';
            }
            for (int j = 0; j < 10; j++){ //Getting random numbers for right obstacles on z-axis
                rightObstacles[j].x = 3;
                rightObstacles[j].y = 1;
                rightObstacles[j].z = rand()%1000 + -500;
//                cout << "\nrandom numbers for RIGHT obstacles on z-axis: " << rightObstacles[j].z << '\n';
            }
            for (int r = 0; r < 3; r++)
            {
                boostItems[r].x = -3;
                boostItems[r].y = 1;
                boostItems[r].z = rand()%1000 + -500;
//                cout << "\nrandom numbers for BOOST ITEMS on z-axis: " << boostItems[r].z << '\n';
            }
            
            break;
        case ' ': /* Press SPACE to pause/continue the game*/
            if (!pauseGame) // true == car is moving
            {
                pauseGame = true; // Car stops moving
//                cout << "\n+++ SPACE is pressed. pauseGame is true. Car's not moving.";
            }
            else
            {
                pauseGame = false; // Car moving
//                cout << "\n--- SPACE is pressed. pauseGame is false. Car's moving.\n";
            }
            break;
        case 'r': /* Press r to replay the game*/
            objCar[0] = 3;
            objCar[1] = 1;
            objCar[2] = 505;
            eyeZ = 520;
            msgLocation = 500;
            objCollision = false;
            visibleObstacles = false;
            pauseGame = false;
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
//        cout << "\nLeft key works\n";
        objCar[0]-=6;
    }
    if (key == GLUT_KEY_RIGHT)
    {
//        cout << "\nRight key works\n";
        objCar[0]+=6;
    }
    glutPostRedisplay();
}

// Initialization routine.
void setup(void){
    glClearColor(1.0, 1.0, 1.0, 0.0); //setting a white blackground to draw on screen
}

/* MARK: OpenGL window reshape routine */
void resize(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// /Applications/Studying/FA21/CSCI_4550/homework4_graphics/homework4_graphics
// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out main.cpp

/* MARK: Main Function */
int main(int argc, char **argv){
    srand(time(0));
    glutInit(&argc, argv);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
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
