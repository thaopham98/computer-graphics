#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>

#define PI 3.14
#define MSEC_PER_FRAME 33.3

bool pauseMotion = false; // stop spinning
bool transforms = false;

bool triangle = false;
bool diamond = false;
bool star = false;
bool cross = false;

bool starMenu = false;
bool diamondMenu = false;
bool triangleMenu= false;
bool crossMenu = false;

static float colors[3];

static int width, height;
/* ---------- The center point ---------- */
int obj_x = 250;
int obj_y = 250;

float m_x = 250;
float m_y = 250;

int rotZ;
int totalDegree;
int pointedShape;
int shapeIndex;

int rotR = 0;
int totalDegreeR=90;

int size = 50;

int numVertices = 250;
int bigCircle = size * 7;
float Radius = bigCircle/2;
float smallCircle = bigCircle - (size/3);
float smallRadius = smallCircle/2;

/* ---------- ARROW FUNCTION ---------- */
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
/* ---------- ARROW FUNCTION ---------- */
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
    glVertex3f(x, y+(size*3/2), 0.0);       //top
    glEnd();
}
/* ---------- DIAMOND FUNCTION ---------- */
void drawDiamond(float x, float y, int size){
    glBegin(GL_POLYGON);
    glVertex3f(x, y-size*2.0, 0.0); //top
    glVertex3f(x-size/2, y-size*2.5, 0.0); //left
    glVertex3f(x, y-size*3.0, 0.0); //bottom
    glVertex3f(x+size/2, y-size*2.5, 0.0); //right
    glEnd();
}
void draw_Diamond(float x, float y, int size){ // DRAW OUTLINE FOR DIAMOND
    glBegin(GL_POLYGON);
    glVertex3f(x, y-size*1.9, 0.0); //top
    glVertex3f(x-size*0.6, y-size*2.5, 0.0); //left
    glVertex3f(x, y-size*3.1, 0.0); //bottom
    glVertex3f(x+size*0.6, y-size*2.5, 0.0); //right
    glEnd();
}
/* ---------- DIAMOND FUNCTION ---------- */
void drawTriangle(float x, float y, int size){
    glBegin(GL_TRIANGLES);
    glVertex3f(x+size/2, y+size*2.0, 0.0); //right
    glVertex3f(x-size/2, y+size*2.0, 0.0); //left
    glVertex3f(x, y+(size*3.0), 0.0); //top
    glEnd();
}
void draw_Triangle(float x, float y, int size){ // DRAW OUTLINE FOR TRIANGLE
    glBegin(GL_TRIANGLES);
    glVertex3f(x+size*0.6, y+size*1.93, 0.0); //right
    glVertex3f(x-size*0.6, y+size*1.93, 0.0); //left
    glVertex3f(x, y+size*3.1, 0.0); //top
    glEnd();
}
/* ---------- DIAMOND FUNCTION ---------- */
void drawCross(float x, float y, int size){
    glBegin(GL_POLYGON);// vertical
    glVertex3f(x+size*2.75, y + size/2, 0.0); // top left
    glVertex3f(x+size*2.75, y - size/2, 0.0); // bottom left
    glVertex3f(x+size*2.5, y - size/2, 0.0); // bottom right
    glVertex3f(x+size*2.5, y + size/2, 0.0); // top right
    glEnd();
    glBegin(GL_POLYGON); // horizontal
    glVertex3f(x+size*2.10, y+size/8, 0.0); //top left
    glVertex3f(x+size*2.10, y-size/8, 0.0); //bottom left
    glVertex3f(x+size*3.15, y-size/8, 0.0); //bottom right
    glVertex3f(x+size*3.15, y+size/8, 0.0); //top right
    glEnd();
}
void draw_Cross(float x, float y, int size){ // DRAW OUTLINE FOR CROSS
    glBegin(GL_POLYGON);// vertical
    glVertex3f(x+size*2.8, y + size*0.55, 0.0); // top left
    glVertex3f(x+size*2.8, y - size*0.55, 0.0); // bottom left
    glVertex3f(x+size*2.45, y - size*0.55, 0.0); // bottom right
    glVertex3f(x+size*2.45, y + size*0.55, 0.0); // top right
    glEnd();
    glBegin(GL_POLYGON); // horizontal
    glVertex3f(x+size*2.05, y+size*0.15, 0.0); //top left
    glVertex3f(x+size*2.05, y-size*0.15, 0.0); //bottom left
    glVertex3f(x+size*3.20, y-size*0.15, 0.0); //bottom right
    glVertex3f(x+size*3.20, y+size*0.15, 0.0); //top right
    glEnd();
}
/* ---------- DIAMOND FUNCTION ---------- */
void drawStar(float x, float y, int size){
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x-size*2.5, y, 0.0);                 //0
    glVertex3f(x-size*2.63, y+size*0.18, 0.0);      //1
    glVertex3f(x-size*2.5, y+size/2, 0.0);          //2
    glVertex3f(x-size*2.37, y+size*0.18, 0.0);      //3
    glVertex3f(x-size*2, y+size*0.14, 0.0);         //4
    glVertex3f(x-size*2.28, y-size*0.11, 0.0);      //5
    glVertex3f(x-size*2.13, y-size/2, 0.0);         //6
    glVertex3f(x-size*2.5, y-size/4, 0.0);          //7
    glVertex3f(x-size*2.85, y-size/2, 0.0);         //8
    glVertex3f(x-size*2.72, y-size*0.11, 0.0);      //9
    glVertex3f(x-size*3, y+size*0.14, 0.0);         //10
    glVertex3f(x-size*2.63, y+size*0.18, 0.0);      //11
    glEnd();
}
void draw_Star(float x, float y, int size){ // DRAW OUTLINE FOR STAR
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x-size*2.5, y, 0.0);             //0
    glVertex3f(x-size*2.66, y+size*0.21, 0.0);  //1
    glVertex3f(x-size*2.5, y+size*0.56, 0.0);   //2
    glVertex3f(x-size*2.34, y+size*0.21, 0.0);  //3
    glVertex3f(x-size*1.9, y+size*0.11, 0.0);   //4
    glVertex3f(x-size*2.23, y-size*0.14, 0.0);  //5
    glVertex3f(x-size*2.11, y-size*0.53, 0.0);  //6
    glVertex3f(x-size*2.5, y-size*0.29, 0.0);   //7
    glVertex3f(x-size*2.88, y-size*0.53, 0.0);  //8
    glVertex3f(x-size*2.76, y-size*0.13, 0.0);  //9
    glVertex3f(x-size*3.1, y+size*0.11, 0.0);   //10
    glVertex3f(x-size*2.66, y+size*0.21, 0.0);  //11
    glEnd();
}
/* ---------- TEXT FUNCTIONS ---------- */
void writeBitmapString(void *font, char *string){
    for (char* c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}
void textStar(float x, float y, int size){
    glRasterPos3f(x*0.38, y*0.2, 0.0);
    writeBitmapString(GLUT_BITMAP_8_BY_13,"Star is Selected. Press \"SPACE\" to Spint");
}
void textDiamond(float x, float y, int size){
    glRasterPos3f(x*0.38, y*0.2, 0.0);
    writeBitmapString(GLUT_BITMAP_8_BY_13,"Diamond is Selected. Press \"SPACE\" to Spint");
}
void textTriangle(float x, float y, int size){
    glRasterPos3f(x*0.38, y*0.2, 0.0);
    writeBitmapString(GLUT_BITMAP_8_BY_13,"Triangle is Selected. Press \"SPACE\" to Spint");
}
void textCross(float x, float y, int size){
    glRasterPos3f(x*0.38, y*0.2, 0.0);
    writeBitmapString(GLUT_BITMAP_8_BY_13,"Cross is Selected. Press \"SPACE\" to Spint");
}
void textWin(float x, float y, int size){
    glRasterPos3f(x*0.85, y*0.1, 0.0);
    writeBitmapString(GLUT_BITMAP_8_BY_13,"You win!");
}
void textLose(float x, float y, int size){
    glRasterPos3f(x*0.85, y*0.1, 0.0);
    writeBitmapString(GLUT_BITMAP_8_BY_13,"You lose!");
}

void mouseControl(int button, int state, int x, int y)
{
    m_x = x;
    m_y = y;
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        //printf("%f %f\n",x,y);
        std::cout << "\nThe coordinate of x is " << x << " The coordinate of y is " << y << "\n";
        std::cout<<"\nLeft click works\n";
        if (200<=m_x && m_x<=300 && m_y<=150 && m_y>=70) //triangle
        {
            triangle = true;
            diamond = false;
            cross = false;
            star = false;
            shapeIndex = 0;
        }
        else if (200<=m_x && m_x<=300 && 370<=m_y && m_y<=430)//diamond
        {
            triangle = false;
            diamond = true;
            cross = false;
            star = false;
            shapeIndex = 2;
            
            
        }
        else if (370<=m_x && m_x<=440 && 220<=m_y && m_y<=280)//cross
        {
            triangle = false;
            diamond = false;
            cross = true;
            star = false;
            shapeIndex = 1;
        }
        else if (70<=m_x && m_x<=130 && 220<=m_y && m_y<=280) //star
        {
            triangle = false;
            diamond = false;
            cross = false;
            star = true;
            shapeIndex= 3;
        }
        else{
            triangle = false;
            diamond = false;
            cross = false;
            star = false;
        }
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        if (70<=m_x && m_x<=130 && 220<=m_y && m_y<=280) // star
            {
                starMenu = true;
                diamondMenu = false;
                triangleMenu = false;
                crossMenu=false;
                glutAttachMenu(GLUT_RIGHT_BUTTON);
            }
            else if (200<=m_x && m_x<=300 && m_y<=150 && m_y>=70) //triangle
            {
                starMenu = false;
                diamondMenu = false;
                triangleMenu = true;
                crossMenu=false;
                glutAttachMenu(GLUT_RIGHT_BUTTON);
            }
    }

    glutPostRedisplay();
}

void motionFunc(int x, int y){
    m_x = x;
    m_y = y;
    if (200<=m_x && m_x<=300 && 370<=m_y && m_y<=430)//diamond
    {
        diamondMenu = true;
        starMenu = false;
        triangleMenu = false;
        crossMenu=false;
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
    else if (70<=m_x && m_x<=130 && 220<=m_y && m_y<=280) // star
    {
        starMenu = true;
        diamondMenu = false;
        triangleMenu = false;
        crossMenu=false;
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
    else if (200<=m_x && m_x<=300 && m_y<=150 && m_y>=70) //triangle
    {
        starMenu = false;
        diamondMenu = false;
        triangleMenu = true;
        crossMenu=false;
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
    else if (370<=m_x && m_x<=440 && 220<=m_y && m_y<=280)//cross
    {
        starMenu = false;
        diamondMenu = false;
        triangleMenu = false;
        crossMenu=true;
        glutAttachMenu(GLUT_RIGHT_BUTTON);
    }
    else
        glutDetachMenu(GLUT_RIGHT_BUTTON);
}

void menuFunc(int id)
{
    if (id == 1){
        colors[0] = 0.7; colors[1] = 0.3; colors[2] = 0.9;
    }
    else if (id == 2){
        colors[0] = 1.0; colors[1] = 0.6; colors[2] = 0.1;
    }
    else if (id == 3){
        colors[0] = 0.0; colors[1] = 1.0; colors[2] = 1.0;
    }
    else if (id == 4){
        colors[0] = 1.0; colors[1] = 0.5; colors[2] = 1.0;
    }
    else if (id == 5){
        colors[0] = 1.0; colors[1] = 1.0; colors[2] = 0.0;
    }
    else if (id == 6){
        colors[0] = 1.0; colors[1] = 0.0; colors[2] = 0.0;
    }
    else if (id == 7){
        colors[0] = 0.0; colors[1] = 1.0; colors[2] = 0.0;
    }
    else if (id == 8){
        colors[0] = 0.0; colors[1] = 0.0; colors[2] = 1.0;
    }
    glutPostRedisplay();
}
void makeMenu()
{
    glutCreateMenu(menuFunc);
    glutAddMenuEntry("Purple", 1);
    glutAddMenuEntry("Organe", 2);
    glutAddMenuEntry("Cyan", 3);
    glutAddMenuEntry("Pink", 4);
    glutAddMenuEntry("Yellow", 5);
    glutAddMenuEntry("Red", 6);
    glutAddMenuEntry("Green", 7);
    glutAddMenuEntry("Blue", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // Attach menu to a mouse button
}
/* -------------------- Keyboard input processing routine -------------------- */
void keyInput(unsigned char key, int x, int y)
{
    int randNumber;
    switch (key)
    {
        case 27:
            exit(0);
            break;
        /* ---------- ROTATING THE ARROW ----------*/
        case ' ':
            if (triangle || diamond || star || cross)
            {
                rotZ = 0;
                randNumber = rand()%13 + 3;
                totalDegree = randNumber * 90;
                std::cout << "\nWhen click SPACE, the random number is: " << randNumber <<'\n';
                pointedShape = randNumber%4;
                if (pauseMotion) // true == stop spinning
                    pauseMotion = false; // spin the arrow
            }
            break;
            
        /* ---------- THE SHAPES ---------- */
        case 'R':
        case 'r':
            rotR = 0;
            transforms = true;
            totalDegreeR = 1 * 90;
            if (pauseMotion)
            {
                pauseMotion = false;
                transforms = true;
            }
            else
            {
                pauseMotion = true;
                transforms = false;
            }
            break;
        default:
            break;
    }
}

void timerFunc(int value)
{
    /* --- Spinning the arrow --- */
    if (!pauseMotion)//true == spinning
    {
        if(rotZ < totalDegree)//true == spinning the arrow
            rotZ = (rotZ + 5);
        else if (rotZ == totalDegree)
            pauseMotion=true;
    }
    /* --- Spinning the shapes --- */
    else if(transforms == true)
    {
        if (rotR < totalDegreeR) // true == spinning the shapes
            rotR = (rotR + 5);
        else if (rotZ == totalDegree)
            pauseMotion = true;
    }
    glutPostRedisplay();
    glutTimerFunc(MSEC_PER_FRAME, timerFunc, value);
}

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    
    /* -------------------- GRAY CIRCLE -------------------- */
    glColor3f(0.8, 0.8, 0.8); drawCirle(Radius, obj_x, obj_y, numVertices,bigCircle);
    
    /* -------------------- WHITE CIRCLE -------------------- */
    glColor3f(1.0, 1.0, 1.0); drawCirle(smallRadius, obj_x, obj_y, numVertices, smallCircle);
    
    /* -------------------- BLACK FRAMES FOR THE SHAPES -------------------- */
    if (triangle){
        glColor3f(0.0,0.0,0.0);
        draw_Triangle(obj_x, obj_y, size);
        textTriangle(obj_x, obj_y, size);
    }
    else if (cross){
        glColor3f(0.0,0.0,0.0);
        draw_Cross(obj_x, obj_y, size);
        textCross(obj_x, obj_y, size);
    }
    else if (diamond){
        glColor3f(0.0,0.0,0.0);
        draw_Diamond(obj_x, obj_y, size);
        textDiamond(obj_x, obj_y, size);
    }
    else if (star){
        glColor3f(0.0, 0.0, 0.0);
        draw_Star(obj_x, obj_y, size);
        textStar(obj_x,obj_y,size);
    }
    
    /* -------------------- WIN && LOSE texts -------------------- */
    if (pauseMotion && (triangle || diamond || star || cross)){
        if(shapeIndex == pointedShape)
            textWin(obj_x, obj_y, size);
        else if (shapeIndex != pointedShape)
            textLose(obj_x, obj_y, size);
    }
    
    glLoadIdentity();
    
    /* -------------------- Transformations for the ARROW -------------------- */
    glTranslatef(250.0 , 250.0 , 0.0);
    glRotatef(rotZ, 0 , 0 , -1); // rotating from right to left
    glTranslatef(-250.0 , -250.0 , 0.0); // orgininal location

    /* --- DRAWING ARROW --- */
    glColor3f(0.5, 0.35, 0.05);
    drawArrow(obj_x,obj_y,size);
    glLoadIdentity();
    
    /* -------------------- Transformations for the shapes -------------------- */
    if (transforms == true){
        glColor3f(1.0, 0.0, 0.0);
        glRotatef(rotR, 0 , 0 , 1);
        glTranslated(120.0, 0.0, 0.0);
        glRotatef(-rotR, 0 , 0 , 1);
        drawCross(119.5, 250.0, size);
        glLoadIdentity();

        /* --- YELLOW DIAMOND --- */
        glColor3f(1.0, 1.0, 0.0);
        glRotatef(rotR, 0 , 0 , 1);
        glTranslated(0.0, -120.0, 0.0);
        glRotatef(-rotR, 0 , 0 , 1);
        drawDiamond(250.0, 375.0, size);
        glLoadIdentity();

        /* --- GREEN STAR --- */
        glColor3f(0.0, 1.0, 0.0);
        glRotatef(rotR, 0 , 0 , 1);
        glTranslated(-120, 0.0, 0.0);
        glRotatef(-rotR, 0 , 0 , 1);
        drawStar(375, 250.0, size);
        glLoadIdentity();

        /* --- BLUE TRIANGLE --- */
        glColor3f(0.0, 0.0, 1.0);
        glRotatef(rotR, 0 , 0 , 1);
        glTranslated(0.0, 120.0, 0.0);
        glRotatef(-rotR, 0 , 0 , 1);
        drawTriangle(250.0, 125.0, size);
    }
    else
    {
        /* --- RED CROSS --- */
        if (crossMenu)
            glColor3fv(colors);
        else
            glColor3f(1.0, 0.0, 0.0);
        drawCross(obj_x, obj_y, size);
        
        /* --- YELLOW DIAMOND --- */
        if (diamondMenu)
            glColor3fv(colors);
        else
            glColor3f(1.0,1.0, 0.0);
        drawDiamond(obj_x, obj_y, size);
        
        /* --- GREEN STAR --- */
        if(starMenu)
            glColor3fv(colors);
        else
            glColor3f(0.0, 1.0, 0.0);
        drawStar(obj_x, obj_y, size);
        
        /* --- BLUE TRIANGLE --- */
        if(triangleMenu)
            glColor3fv(colors);
        else
            glColor3f(0.0, 0.0, 1.0);
        drawTriangle(obj_x, obj_y, size);
    }
    /* --- BLACK DOT ---- */
    glColor3f(0.0, 0.0, 0.0);
    drawCirle(1, obj_x, obj_y, numVertices, 2);
    
    glDisable(GL_DEPTH_TEST);
    glFlush();
}

// Initialization routine.
void setup(void){
    glClearColor(1.0, 1.0, 1.0, 0.0); //setting a white blackground to draw on
    makeMenu();
}
// OpenGL window reshape routine.
void resize(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    width = w; height = h;
    glOrtho(0.0, w, 0.0, h, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// /Applications/Studying/FA21/CSCI_4550/homework3_graphics/homework3_graphics
// g++ -framework OpenGL -lGLUT -lGLEW -I /opt/X11/include -L /opt/X11/lib -w -o out main.cpp
int main(int argc, char **argv){
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
    glutTimerFunc(MSEC_PER_FRAME, timerFunc, 1);
    glutMouseFunc(mouseControl);
    glutPassiveMotionFunc(motionFunc);
    glewExperimental = GL_TRUE;
    glewInit();
    setup();
    glutMainLoop();
}
