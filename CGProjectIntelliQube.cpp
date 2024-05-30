
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>      // handle the window-managing operations
#else
#include <GL/glew.h>
#include <GL/freeglut.h>    // handle the window-managing operations
#endif
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
GLint win_width = 600,
win_hight = 600;

float transValue;
float scaleValue;
float scale1 = 0.0;
float translation = 0.0;

bool L1 = false;
bool L2 = false;
bool L3 = false;
bool L4 = false;
bool L5 = false;
bool L6 = false;
//level 2
int level2Games = 1;
int skipLevel2 = 1;
//level 3
bool transitionToScene2 = false;
//level 4
int page = 0;
int KeyboardMove = 0;
//Prize Page
GLuint myTexture;
char image1Path[] = "C:\\Users\\083T\\Downloads\\FinalDraw\\ThePrize.bmp";
// basic
int flag = 0;
int moveLevel = 0;
int CountmoveLevel = 0;
int skip = 1;
int CountSkip = 0;
int startGame = 0;
int IQ = 0;
string CountIQ;
float scale = 0.0; //control scale +,-
int gap = 300; //func "MyTimer"
int counter = 0; //func "MyTimer"
int timeControl = 0; //func "MyTimer"
int next1 = 0; //game page transition
int keyMouse1 = 0; //key mouse
GLdouble PI = 3.14159265359;

// -------------------------[ Build Fanction ]-------------------------

//Font Type:
//GLUT_BITMAP_HELVETICA_18
//GLUT_BITMAP_TIMES_ROMAN_24
//GLUT_BITMAP_9_BY_15

//track cursor coordinates x,y
void mouseTracking(int x, int y) {
    cout << "X: " << x << " ,Y: " << y << endl;
}

//calculating time
void MyTimer(int extra)
{
    if (timeControl == 0) { //on
        counter = extra + 1;
    }
    if (timeControl == 1) { //stop
        counter = extra + 0;
    }
    if (timeControl == 2) { //start zero
        counter = 0;
    }
    glutPostRedisplay();
    glutTimerFunc(gap, MyTimer, counter);
}

//draw filled circle
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

//draw hollow circle
void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int lineAmount = 100; //# of triangles used to draw circle
    GLfloat twicePi = 2.0f * PI;
    glBegin(GL_LINE_LOOP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}

// -------------------------[ Basic Designs Of The Game ]-------------------------

//background intro
void background1()
{
    //background 
    glBegin(GL_QUADS);
    glColor3f(0.996f, 0.97265625f, 0.89453125f);
    glVertex2f(1.0f, 0.88f);
    glVertex2f(-1.0f, 0.88f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    //three circles
    glColor3f(1.f, 0.0f, 0.f);
    drawFilledCircle(-0.9, 0.94, 0.025);
    glColor3f(0.f, 1.0f, 0.f);
    drawFilledCircle(-0.8, 0.94, 0.025);
    glColor3f(0.2f, 0.5f, 0.9f);
    drawFilledCircle(-0.7, 0.94, 0.025);
}

//background level game
void background2()
{
    //background
    glBegin(GL_QUADS);
    glColor3f(0.996f, 0.97265625f, 0.89453125f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
    //the top bar
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(1.0f, 0.95f);
    glVertex2f(-1.0f, 0.95f);
    glVertex2f(-1.0f, 0.8f);
    glVertex2f(1.0f, 0.8f);
    glEnd();
    //frame top bar
    glBegin(GL_LINES);
    glLineWidth(0.1);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(1.0f, 0.95f);
    glVertex2f(-1.0f, 0.95f);
    glVertex2f(-1.0f, 0.8f);
    glVertex2f(1.0f, 0.8f);
    glEnd();
    //skip level icon
    glBegin(GL_QUADS);
    glLineWidth(0.1);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.915f, 0.905f);
    glVertex2f(0.9f, 0.905f);
    glVertex2f(0.9f, 0.845f);
    glVertex2f(0.915f, 0.845f);
    glEnd();
    glBegin(GL_TRIANGLES);
    glLineWidth(0.1);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.84f, 0.845f);
    glVertex2f(0.895f, 0.875f);
    glVertex2f(0.84f, 0.905f);
    glEnd();
    //text "Skip Level"
    char text1[] = "Skip Level";
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(0.58, 0.85999);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text1[i]);
    }
}

//background of IQ results
void background3()
{
    //frame 1
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.45f, 0.45f, 0.45f);
    glVertex2f(0.8f, 0.4f);
    glVertex2f(0.8f, 0.7f);
    glVertex2f(0.5f, 0.7f);
    glEnd();
    //frame 2
    glBegin(GL_LINE_STRIP);
    glColor3f(0.45f, 0.45f, 0.45f);
    glVertex2f(-0.5f, 0.7f);
    glVertex2f(-0.8f, 0.7f);
    glVertex2f(-0.8f, 0.4f);
    glEnd();
    //frame 3
    glBegin(GL_LINE_STRIP);
    glColor3f(0.45f, 0.45f, 0.45f);
    glVertex2f(-0.8f, -0.5f);
    glVertex2f(-0.8f, -0.8f);
    glVertex2f(-0.5f, -0.8f);
    glEnd();
    //frame 4
    glBegin(GL_LINE_STRIP);
    glColor3f(0.45f, 0.45f, 0.45f);
    glVertex2f(0.5f, -0.8f);
    glVertex2f(0.8f, -0.8f);
    glVertex2f(0.8f, -0.5f);
    glEnd();
    //button box
    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.6f, 0.5f);
    glVertex2f(0.28f, -0.72f);
    glVertex2f(-0.28f, -0.72f);
    glVertex2f(-0.28f, -0.85f);
    glVertex2f(0.28f, -0.85f);
    glEnd();
}

// ---------------------------------------------------------------[ Introduction 1 ]---------------------------------------------------------------
void Page1()
{
    //cube
    glBegin(GL_QUADS); //up
    glColor3f(0.515625f, 0.703125f, 0.875f);
    glVertex2f(0.0f, 0.25f);
    glVertex2f(-0.2f, 0.15f);
    glVertex2f(0.0f, 0.05f);
    glVertex2f(0.2f, 0.15f);
    glEnd();
    glBegin(GL_QUADS); //left
    glColor3f(0.996f, 0.54296f, 0.54296f);
    glVertex2f(-0.2f, 0.15f);
    glVertex2f(-0.2f, -0.05f);
    glVertex2f(0.0f, -0.15f);
    glVertex2f(0.0f, 0.05f);
    glEnd();
    glBegin(GL_QUADS); //right
    glColor3f(0.996f, 0.84765f, 0.39843f);
    glVertex2f(0.0f, 0.05f);
    glVertex2f(0.0f, -0.15f);
    glVertex2f(0.2f, -0.05f);
    glVertex2f(0.2f, 0.15f);
    glEnd();
    //line cube
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.2f, 0.15f); //left
    glVertex2f(0.0f, 0.05f);
    glVertex2f(0.0f, 0.05f); //right
    glVertex2f(0.2f, 0.15f);
    glVertex2f(0.0f, 0.05f); //mid
    glVertex2f(0.0f, -0.15f);
    glEnd();
}

void textPage1()
{
    //text
    char text1[] = "IntelliQube";
    glColor3f(0.36, 0.36, 0.36);
    glRasterPos2f(-0.18, -0.29);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
}

// --> Introduction 1 - Move the cube
void Introduction()
{
    //hide the cube
    glPushMatrix();
    glScalef(0.0, .0, 0.0);
    Page1();
    glPopMatrix();
    //show the cube
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0, 0.04, 0.0);
    glScalef(scale, scale, 0.0);
    Page1();
    if (scale < 1.0) {
        scale = scale + 0.0005;
    }
    glPopMatrix();
    //show name of the game
    if (scale >= 1.0) {
        glPushMatrix();
        glTranslatef(0.0, 0.06, 0.0);
        textPage1();
        glPopMatrix();
    }
}

// ---------------------------------------------------------------[ Introduction 2 ]---------------------------------------------------------------
void Page2() //game definition
{
    keyMouse1 = 1;
    background1();

    //text box
    glBegin(GL_QUADS);
    glLineWidth(0.1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.8f, 0.45f);
    glVertex2f(-0.8f, 0.45f);
    glVertex2f(-0.8f, -0.55f);
    glVertex2f(0.8f, -0.55f);
    glEnd();
    //next box
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.2f, -0.65f);
    glVertex2f(-0.2f, -0.65f);
    glVertex2f(-0.2f, -0.76f);
    glVertex2f(0.2f, -0.76f);
    glEnd();
    //next frame
    glBegin(GL_LINE_LOOP);
    glLineWidth(0.1);
    glColor3f(0.85f, 0.85f, 0.85f);
    glVertex2f(0.2f, -0.65f);
    glVertex2f(-0.2f, -0.65f);
    glVertex2f(-0.2f, -0.76f);
    glVertex2f(0.2f, -0.76f);
    glEnd();
    //text "Next"
    char text7[] = "Next";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.071, -0.72);
    for (GLint i = 0; i <= strlen(text7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text7[i]);
    }

    //text "Welcome"
    char text2[] = "Welcome to IntelliQube !";
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.4, 0.62);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
    }
    //text intro project
    char text3[] = "The IntelliQube is a puzzle game";
    char text4[] = "that contains six different levels of ";
    char text5[] = "difficulty to determine the player's";
    char text6[] = "intelligence quotient(IQ) level.";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.53, 0.20);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text3[i]);
    }
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.56, 0.03);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text4[i]);
    }
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.56, -0.13);
    for (GLint i = 0; i <= strlen(text5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text5[i]);
    }
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.51, -0.31);
    for (GLint i = 0; i <= strlen(text6); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text6[i]);
    }
}

// ---------------------------------------------------------------[ Introduction 3 ]---------------------------------------------------------------
void Page3() //game rules
{
    keyMouse1 = 2;
    background1();

    //text box
    glBegin(GL_QUADS);
    glLineWidth(0.2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.83f, 0.62f);
    glVertex2f(-0.83f, 0.62f);
    glVertex2f(-0.83f, -0.69f);
    glVertex2f(0.83f, -0.69f);
    glEnd();
    //next box
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.2f, -0.73f);
    glVertex2f(-0.2f, -0.73f);
    glVertex2f(-0.2f, -0.84f);
    glVertex2f(0.2f, -0.84f);
    glEnd();
    //next frame
    glBegin(GL_LINE_LOOP);
    glLineWidth(0.1);
    glColor3f(0.85f, 0.85f, 0.85f);
    glVertex2f(0.2f, -0.73f);
    glVertex2f(-0.2f, -0.73f);
    glVertex2f(-0.2f, -0.84f);
    glVertex2f(0.2f, -0.84f);
    glEnd();
    //text "Next"
    char text8[] = "Next";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.071, -0.8);
    for (GLint i = 0; i <= strlen(text8); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text8[i]);
    }

    //text "Rules"
    char text7[] = "Game Rules";
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.19, 0.69);
    for (GLint i = 0; i <= strlen(text7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text7[i]);
    }
    //text game rules
    char text3[] = "# This game will have six levels, and you";
    char text4[] = "  must solve them within three minutes.";
    char text5[] = "# If you complete a certain level, you will";
    char text6[] = "  automatically move to the next level, and";
    char text9[] = "  if you do not know the solution for specific";
    char text10[] = "  level, you can skip it 'YOU CAN'T BACK'.";
    char text11[] = "# If you finish all the levels within the";
    char text12[] = "  specified time, your result will appear";
    char text13[] = "  immediately, If all the answers are correct";
    char text14[] = "  you will get the prize. Otherwise, the";
    char text15[] = "  game will end and an incomplete result";
    char text16[] = "  will appear. You can replay the game.";
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, 0.5);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text3[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, 0.4);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text4[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, 0.3);
    for (GLint i = 0; i <= strlen(text5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text5[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, 0.2);
    for (GLint i = 0; i <= strlen(text6); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text6[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, 0.1);
    for (GLint i = 0; i <= strlen(text9); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text9[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, 0.0);
    for (GLint i = 0; i <= strlen(text10); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text10[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, -0.1);
    for (GLint i = 0; i <= strlen(text11); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text11[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, -0.2);
    for (GLint i = 0; i <= strlen(text12); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text12[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, -0.3);
    for (GLint i = 0; i <= strlen(text13); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text13[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, -0.4);
    for (GLint i = 0; i <= strlen(text14); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text14[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.74, -0.5);
    for (GLint i = 0; i <= strlen(text15); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text15[i]);
    }
    glColor3f(0.3, 0.3, 0.3);
    glRasterPos2f(-0.75, -0.6);
    for (GLint i = 0; i <= strlen(text16); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text16[i]);
    }
}

// ---------------------------------------------------------------[ Start Window ]---------------------------------------------------------------
void Page4()
{
    keyMouse1 = 3;
    background1();

    //frame
    glLineWidth(3.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.4, 0.4, 0.4);
    glVertex2f(-0.86f, -0.35f);
    glVertex2f(0.86f, -0.35f);
    glVertex2f(0.86f, 0.6f);
    glVertex2f(-0.86f, 0.6f);
    glEnd();
    //circle start
    glColor3f(1.0, 1.0, 1.0);
    drawFilledCircle(0.0, 0.1, 0.14);
    //triangle start
    glBegin(GL_TRIANGLES);
    glColor3f(0.3, 0.3, 1.3);
    glVertex2f(-0.05, 0.18);
    glVertex2f(-0.05, 0.03);
    glVertex2f(0.1, 0.10);
    glEnd();
    //cloud circles
    glColor3f(0.537254902, 0.8117647059, 0.9411764706);
    drawFilledCircle(0.0, -0.3, 0.12);

    drawFilledCircle(0.2, -0.3, 0.12);
    drawFilledCircle(0.4, -0.3, 0.12);
    drawFilledCircle(0.5, -0.35, 0.12);

    drawFilledCircle(-0.2, -0.3, 0.12);
    drawFilledCircle(-0.4, -0.3, 0.12);
    drawFilledCircle(-0.5, -0.35, 0.12);

    glColor3f(0.537254902, 0.8117647059, 0.9411764706);
    drawFilledCircle(0.0, -0.4, 0.12);

    drawFilledCircle(0.2, -0.4, 0.12);
    drawFilledCircle(0.4, -0.4, 0.12);

    drawFilledCircle(-0.2, -0.4, 0.12);
    drawFilledCircle(-0.4, -0.4, 0.12);

    //text - project name
    char text12[] = "IntelliQube";
    glColor3f(0.36, 0.36, 0.36);
    glRasterPos2f(-0.181, 0.388);
    for (GLint i = 0; i <= strlen(text12); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text12[i]);
    }
    //text
    char text13[] = "START";
    glColor3f(0.5, 0.5, 0.5);
    glRasterPos2f(-0.11, -0.12);
    for (GLint i = 0; i <= strlen(text13); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text13[i]);
    }
    char text14[] = "<<<< GOOD LUCK >>>>";
    glColor3f(0.4, 0.4, 0.4);
    glRasterPos2f(-0.4, -0.38);
    for (GLint i = 0; i <= strlen(text14); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text14[i]);
    }
    char text15[] = "ARE YOU READY!!!";
    glColor3f(0.4, 0.4, 0.4);
    glRasterPos2f(-0.3, -0.7);
    for (GLint i = 0; i <= strlen(text15); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text15[i]);
    }
}

// ---------------------------------------------------------------[ Level 1 ]---------------------------------------------------------------
// Find the different face - Afnan Mahmoud Dahlan

//the half circle (up)
void drawFilledCircleHalfUp(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 50; //# of triangles used to draw circle
    GLfloat twicePi = 1.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); //center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

//the half circle (down)
void drawFilledCircleHalfDown(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 50; //# of triangles used to draw circle
    GLfloat twicePi = -1.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

//the Screen Frame (black)
void ScreenFrame()
{
    glLineWidth(1.5f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(-0.86f, -0.96f);
    glVertex2f(0.86f, -0.96f);
    glVertex2f(0.86f, 0.539f);
    glVertex2f(-0.86f, 0.539f);
    glEnd();
}

//the face object (SAD)
void FaceSad()
{
    //the face
    glColor3f(1.0f, 0.8f, 0.2f);
    drawFilledCircle(0.74, 0.84, .1);
    //the eyes
    glColor3f(0.6f, 0.4f, 0.0f);
    drawFilledCircle(0.78, 0.86, .015);
    drawFilledCircle(0.71, 0.86, .015);
    //the mouth
    glColor3f(0.6f, 0.4f, 0.0f);
    drawFilledCircleHalfUp(0.745, 0.795, .026);
    //the tear (drop)
    glColor3f(0.1f, 0.6f, 1.0f);
    drawFilledCircle(0.67, 0.786, .0275);

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.6f, 1.0f);
    glVertex2f(0.6399f, 0.786f);
    glVertex2f(0.7f, 0.786f);
    glVertex2f(0.67f, 0.84f);
    glEnd();
}

//the different face (SMILE)
void FaceSmile()
{
    //the face
    glColor3f(1.0f, 0.8f, 0.2f);
    drawFilledCircle(0.74, 0.84, .1);
    //the eyes
    glColor3f(0.6f, 0.4f, 0.0f);
    drawFilledCircle(0.78, 0.86, .015);
    drawFilledCircle(0.71, 0.86, .015);
    //the mouth
    glColor3f(0.6f, 0.4f, 0.0f);
    drawFilledCircleHalfDown(0.745, 0.815, .0255);
    // the tear (drop)
    glColor3f(0.1f, 0.6f, 1.0f);
    drawFilledCircle(0.67, 0.786, .0275);

    glBegin(GL_TRIANGLES);
    glColor3f(0.1f, 0.6f, 1.0f);
    glVertex2f(0.6399f, 0.786f);
    glVertex2f(0.7f, 0.786f);
    glVertex2f(0.67f, 0.84f);
    glEnd();
}

void game1()
{
    ScreenFrame();

    //////////////////
    //Line 1
    //////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.21, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.42, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.63, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.84, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.05, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.26, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.47, -0.38, 0.0);
    FaceSad();
    glPopMatrix();

    //////////////////
    //Line 2
    //////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.21, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.42, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.63, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.84, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.05, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.26, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.47, -0.59, 0.0);
    FaceSad();
    glPopMatrix();

    //////////////////
    //Line 3
    //////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.21, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.42, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.63, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.84, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.05, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.26, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.47, -0.8, 0.0);
    FaceSad();
    glPopMatrix();

    //////////////////
    //Line 4
    //////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.21, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.42, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.63, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.84, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.05, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.26, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.47, -1.01, 0.0);
    FaceSad();
    glPopMatrix();

    //////////////////
    //Line 5
    //////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, -1.22, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.21, -1.22, 0.0);
    FaceSad();
    glPopMatrix();

    ///////////////////////////////////
    // the different face        
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.42, -1.22, 0.0);
    FaceSmile();
    glPopMatrix();
    ///////////////////////////////////

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.63, -1.22, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.84, -1.22, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.05, -1.22, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.26, -1.22, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.47, -1.22, 0.0);
    FaceSad();
    glPopMatrix();

    //////////////////
    //Line 6
    //////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.21, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.42, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.63, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.84, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.05, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.26, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.47, -1.43, 0.0);
    FaceSad();
    glPopMatrix();

    //////////////////
    //Line 7
    //////////////////
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.0, -1.64, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.21, -1.64, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.42, -1.64, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.63, -1.64, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.84, -1.64, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.05, -1.64, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.26, -1.64, 0.0);
    FaceSad();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-1.47, -1.64, 0.0);
    FaceSad();
    glPopMatrix();
}

//Page Level 1
void Level1()
{
    keyMouse1 = 4;

    background2();
    //text "Level 1"
    char text1[] = "Lev.1   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85); //-0.915, 0.85
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
    //question text
    char text2[] = "Find the different shape !";
    glColor3f(0.3, 0.6, 0.2);
    glRasterPos2f(-0.40, 0.65);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
    }

    glPushMatrix();
    glTranslatef(0.0, 0.04, 0.0);
    game1();
    glPopMatrix();

    //draw a circle for the correct answer
    if (flag == 1) {
        glColor3f(0.9f, 0.2f, 0.3f);
        drawHollowCircle(0.32, -0.383, 0.14);
    }
}

// ---------------------------------------------------------------[ Level 2 ]---------------------------------------------------------------
// Colors game - Aseel Alsayed

//Page Level 2
void level2Game1()
{
    keyMouse1 = 5;

    background2();
    //text "Level 2"
    char text1[] = "Lev.2   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }

    //text
    char msg5[] = "1. Pick The Red Color";
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.34, 0.62);
    for (int i = 0; i < strlen(msg5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg5[i]);
    }

    //circle 1
    glColor4f(0.7f, 0.9f, 0.2f, 0.2f);
    drawFilledCircle(0.0, 0.36, 0.14);
    //frame circle 1
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, 0.36, 0.15);
    //text circle 1
    char msg1[] = "RED";
    glRasterPos3f(-0.05, 0.345, 0.0);
    for (int i = 0; i < strlen(msg1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg1[i]);
    }

    //circle 2
    glColor4f(1.0f, 0.6f, 0.2f, 0.1f);
    drawFilledCircle(0.0, 0.0, 0.14);
    //frame circle 2
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, 0.0, 0.15);
    //text circle 2
    char msg2[] = "GREEN";
    glRasterPos3f(-0.077, -0.01, 0.0);
    for (int i = 0; i < strlen(msg2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg2[i]);
    }

    //circle 3
    glColor4f(0.40f, 0.3f, 1.0f, .1f);
    drawFilledCircle(0.0, -0.35, 0.14);
    //frame circle 3
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, -0.35, 0.15);
    //text circle 3
    char msg3[] = "  YALLOW  ";
    glRasterPos3f(-0.158, -0.365, 0.0);
    for (int i = 0; i < strlen(msg3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg3[i]);
    }

    //circle 4
    glColor4f(0.8f, .0f, .0f, 0.1f);
    drawFilledCircle(0.0, -0.7, 0.14);
    //frame circle 4
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, -0.7, 0.15);
    //text circle 4
    char msg4[] = "   PINK  ";
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.155, -0.715, 0.0);
    for (int i = 0; i < strlen(msg4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg4[i]);
    }
}

void level2Game2()
{
    keyMouse1 = 6;

    background2();
    //text "Level 2"
    char text1[] = "Lev.2   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }

    //text
    char msg5[] = "2. Pick The White Color";
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.36, 0.62);
    for (int i = 0; i < strlen(msg5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg5[i]);
    }

    //circle 1
    glColor4f(1.0f, 1.0f, 1.f, 0.2f);
    drawFilledCircle(0.0, 0.36, 0.14);
    //frame circle 1
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, 0.36, 0.15);
    //text circle 1
    char msg1[] = "PINK";
    glRasterPos3f(-0.057, 0.345, 0.0);
    for (int i = 0; i < strlen(msg1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg1[i]);
    }

    //circle 2
    glColor4f(1.0f, 0.f, 1.0f, 0.1f);
    drawFilledCircle(0.0, 0.0, 0.14);
    //frame circle 2
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, 0.0, 0.15);
    //text circle 2
    char msg2[] = "WHITE";
    glRasterPos3f(-0.077, -0.01, 0.0);
    for (int i = 0; i < strlen(msg2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg2[i]);
    }

    //circle 3
    glColor4f(0.40f, 0.3f, 1.0f, .1f);
    drawFilledCircle(0.0, -0.35, 0.14);
    //frame circle 3
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, -0.35, 0.15);
    //text circle 3
    char msg3[] = "  YALLOW  ";
    glRasterPos3f(-0.158, -0.365, 0.0);
    for (int i = 0; i < strlen(msg3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg3[i]);
    }

    //circle 4
    glColor4f(0.99609375f, .796875f, .0f, 0.1f);
    drawFilledCircle(0.0, -0.7, 0.14);
    //frame circle 4
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, -0.7, 0.15);
    //text circle 4
    char msg4[] = "   RED  ";
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.147, -0.715, 0.0);
    for (int i = 0; i < strlen(msg4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg4[i]);
    }
}

void level2Game3()
{
    keyMouse1 = 7;

    background2();
    //text "Level 2"
    char text1[] = "Lev.2   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }

    //text
    char msg5[] = "3. Pick The \"Red\"";
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.3, 0.62);
    for (int i = 0; i < strlen(msg5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg5[i]);
    }

    //circle 1
    glColor4f(0.7f, 0.9f, 0.2f, 0.2f);
    drawFilledCircle(0.0, 0.36, 0.14);
    //frame circle 1
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, 0.36, 0.15);
    //text circle 1
    char msg1[] = "RED";
    glRasterPos3f(-0.05, 0.345, 0.0);
    for (int i = 0; i < strlen(msg1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg1[i]);
    }

    //circle 2
    glColor4f(1.0f, 0.6f, 0.2f, 0.1f);
    drawFilledCircle(0.0, 0.0, 0.14);
    //frame circle 2
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, 0.0, 0.15);
    //text circle 2
    char msg2[] = "WHITE";
    glRasterPos3f(-0.077, -0.01, 0.0);
    for (int i = 0; i < strlen(msg2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg2[i]);
    }

    //circle 3
    glColor4f(0.40f, 0.3f, 1.0f, .1f);
    drawFilledCircle(0.0, -0.35, 0.14);
    //frame circle 3
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, -0.35, 0.15);
    //text circle 3
    char msg3[] = "  BLUE  ";
    glRasterPos3f(-0.13, -0.365, 0.0);
    for (int i = 0; i < strlen(msg3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg3[i]);
    }

    //circle 4
    glColor4f(0.8f, 0.0f, 0.0f, 0.1f);
    drawFilledCircle(0.0, -0.7, 0.14);
    //frame circle 4
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.0, -0.7, 0.15);
    //text circle 4
    char msg4[] = "  YALLOW  ";
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.154, -0.715, 0.0);
    for (int i = 0; i < strlen(msg4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, msg4[i]);
    }
}

// ---------------------------------------------------------------[ Level 3 ]---------------------------------------------------------------
// Spot the 8 differences - Jana Alharthi

///<Differences>
std::vector<std::pair<float, float>> correctDifferences = {
    {0.4520759771341, 0.40848124236230}, //1
    {0.3555978012739, 0.26023571845650}, //2
    {0.2826319792994, 0.05592840815780}, //3
    {0.0858583043946, -0.2064364917153}, //4
    {0.7253727478353, -0.4824662301235}, //5
    {0.7936969405106, -0.4032101666201}, //6
    {0.8319584884088, -0.3048233291677}, //7
    {0.8920837779630,  0.1679800841453}  //8
};
std::vector<std::pair<float, float>> spottedDifferences;
std::vector<int> spottedIndices;

//---------------------------
///       Functions
//---------------------------
/*
 * Function that handles the drawing of a circle using the line loop
 * method. This will create a hollow circle.
 * Params:
 *    x (GLFloat) - the x position of the center point of the circle
 *    y (GLFloat) - the y position of the center point of the circle
 *    radius (GLFloat) - the radius that the painted circle will have
 *    function Source: https://gist.github.com/linusthe3rd/803118
 */
void drawFilledSemicircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 10; //# of triangles used to draw semicircle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of semicircle
    for (i = 0; i <= triangleAmount; i++) {
        GLfloat theta = PI * i / triangleAmount;
        GLfloat px = x + radius * cos(theta);
        GLfloat py = y + radius * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
}

void drawHollowSemicircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 10; //# of triangles used to draw semicircle
    glBegin(GL_LINE_LOOP); // Use GL_LINE_LOOP instead of GL_TRIANGLE_FAN
    for (i = 0; i <= triangleAmount; i++) {
        GLfloat theta = PI * i / triangleAmount;
        GLfloat px = x + radius * cos(theta);
        GLfloat py = y + radius * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
}

//---------------------------
/// The Main Drawing Functions
//---------------------------

void outer_frame() {

    //outer frame cover
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-1.0, 0.495);
    glVertex2f(1.0, 0.495);
    glVertex2f(1.0, 0.56);
    glVertex2f(-1.0, 0.56);
    glEnd();

    //outer frame (A,B boxes)
    glLineWidth(2.0f);
    glColor3f(0.4f, 0.4f, 0.4f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.0, 0.495);
    glVertex2f(1.0, 0.495);
    glVertex2f(1.0, 0.56);
    glVertex2f(-1.0, 0.56);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0, 0.495);
    glVertex2f(0, 0.56);
    glEnd();

    // Text ( A , B )
    glColor3f(0.7, 0.1, 1.0);
    char text1[] = "A";
    glRasterPos2f(-0.5, 0.5);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
    char text2[] = "B";
    glRasterPos2f(0.5, 0.5);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
    }
}

void ground() {
    glBegin(GL_QUADS);
    //white background
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5, 0.9919022083036);
    glVertex2f(0.5, 0.9919022083036);
    glVertex2f(0.5, 0);
    glVertex2f(-0.5, 0);
    //ground
    glColor3f(0.9f, 0.9f, 0.8f);
    glVertex2f(-0.5, 0.73);
    glVertex2f(0.5, 0.73);
    glVertex2f(0.5, 0);
    glVertex2f(-0.5, 0);
    glEnd();
}

void Background() {

    //----------------------- Clouds -----------------------
    ///-1-
    glColor3f(0.7f, 0.7f, 0.7f);
    drawFilledCircle(-0.13, 0.9255486023297, 0.009);
    drawFilledCircle(-0.12, 0.94, 0.01);
    drawFilledCircle(-0.11, 0.9220112655097, 0.015);
    drawFilledCircle(-0.095, 0.95, 0.019);
    drawFilledCircle(-0.08, 0.9220112655097, 0.015);
    drawFilledCircle(-0.07, 0.94, 0.01);
    drawFilledCircle(-0.06, 0.9255486023297, 0.009);
    ///-2-
    glColor3f(0.7f, 0.9f, 1.0f);
    drawFilledCircle(-0.136, 0.9053595203975, 0.009);
    drawFilledCircle(-0.126, 0.9145894316692, 0.01);
    drawFilledCircle(-0.116, 0.9220112655097, 0.015);
    drawFilledCircle(-0.1, 0.929, 0.019);
    drawFilledCircle(-0.084, 0.9220112655097, 0.015);
    drawFilledCircle(-0.074, 0.9145894316692, 0.01);
    drawFilledCircle(-0.064, 0.9053595203975, 0.009);
    //----------------------- The Sun ----------------------
    glColor3f(1.0f, 1.0f, 0.0f);
    drawFilledCircle(0.2040309958178, 0.9452805934321, 0.075);
    ///-sun's Border-
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawHollowCircle(0.1768290125995, 0.9671593144176, 0.04);

    glBegin(GL_QUADS);
    //--------------------- Sun's Rays ---------------------
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex2f(0.0969257264857, 0.9799402491368);
    glVertex2f(0.122071624913, 0.9799402491368);
    glVertex2f(0.122071624913, 0.9696693892158);
    glVertex2f(0.0969257264857, 0.9696693892158);

    glVertex2f(0.1004674023205, 0.934606798451);
    glVertex2f(0.1256575895913, 0.9462305447827);
    glVertex2f(0.1303328264589, 0.9364125473608);
    glVertex2f(0.1055438043504, 0.9243359385301);

    glVertex2f(0.1447202325101, 0.9214949580941);
    glVertex2f(0.1520083857302, 0.9164932843157);
    glVertex2f(0.1259996820822, 0.8746221295417);
    glVertex2f(0.118425718932, 0.8796238033202);

    glVertex2f(0.1714399966131, 0.9119708601186);
    glVertex2f(0.1840980504362, 0.9119708601186);
    glVertex2f(0.1815003618456, 0.8524355480574);
    glVertex2f(0.1714399966131, 0.8524355480574);

    glVertex2f(0.1999403586908, 0.9169531425939);
    glVertex2f(0.2095163266537, 0.9222883247447);
    glVertex2f(0.2381074310003, 0.8681157059828);
    glVertex2f(0.2281210644103, 0.8630541229167);
    //--------------------- Clouds's Base ---------------------
    glColor3f(0.7f, 0.9f, 1.0f);
    glVertex2f(-0.125, 0.914);
    glVertex2f(-0.074, 0.914);
    glVertex2f(-0.064, 0.898);
    glVertex2f(-0.135, 0.898);
    glEnd();
    //----------------------- The Trees -----------------------
    glColor3f(0.4f, 0.6f, 0.2f);
    drawFilledCircle(-0.4213853454832, 0.7786572361154, 0.04);
    glColor3f(0.0f, 0.5f, 0.1f);
    drawFilledCircle(-0.3749053809703, 0.8105046192075, 0.06);
    glColor3f(0.4f, 0.6f, 0.2f);
    drawFilledCircle(-0.0797490013471, 0.7853297371187, 0.045);
    glColor3f(0.1f, 0.4f, 0.2f);
    drawFilledCircle(-0.0409382285443, 0.779517976199, 0.04);
    glColor3f(0.0f, 0.5f, 0.1f);
    drawFilledCircle(0.0046809958851, 0.809643879124, 0.06);
    glColor3f(0.1f, 0.4f, 0.2f);
    drawFilledCircle(0.3203779380671, 0.7986584690995, 0.05);
    glColor3f(0.0f, 0.5f, 0.1f);
    drawFilledCircle(0.3707627234469, 0.8246142676285, 0.06);

    glBegin(GL_TRIANGLES);
    //---------------- Trees' Trunks & Branches ----------------
    glColor3f(0.6f, 0.3f, 0.0f);
    ///-1-
    ///Branches
    glVertex2f(-0.3784339972375, 0.7708501276176);
    glVertex2f(-0.3755444701594, 0.7774425919752);
    glVertex2f(-0.3961678701332, 0.7927021466403);

    glVertex2f(-0.3869457675446, 0.7200421063425);
    glVertex2f(-0.3664623914073, 0.7200421063425);
    glVertex2f(-0.3749053809703, 0.8105046192075);
    ///-2-
    ///Branches
    glVertex2f(-0.0836145858153, 0.7589671545024);
    glVertex2f(-0.0810094238079, 0.7643222097399);
    glVertex2f(-0.0956996429053, 0.7743086641017);

    glVertex2f(-0.0810094238079, 0.7643222097399);
    glVertex2f(-0.0773187776307, 0.7612828540646);
    glVertex2f(-0.0705887757782, 0.7792295256713);
    ///-trunk-
    glVertex2f(-0.0885395093934, 0.7235594813034);
    glVertex2f(-0.0729951527005, 0.7235594813034);
    glVertex2f(-0.0797490013471, 0.7853297371187);
    ///-3-
    ///Branches
    glVertex2f(-0.0442205123447, 0.7535904464741);
    glVertex2f(-0.0407651579533, 0.7583575923089);
    glVertex2f(-0.0535374485464, 0.7670751874756);

    glVertex2f(-0.0407651579533, 0.7583575923089);
    glVertex2f(-0.037995399238, 0.7546020273539);
    glVertex2f(-0.0296163920753, 0.7738178416279);
    ///-trunk-
    glVertex2f(-0.0488484961557, 0.7200421063425);
    glVertex2f(-0.0339150417744, 0.7200421063425);
    glVertex2f(-0.0409382285443, 0.779517976199);
    ///-4-
    ///Branches
    glVertex2f(0.0019823598368, 0.7704867050102);
    glVertex2f(0.00605517072, 0.7770221457297);
    glVertex2f(-0.0170693951486, 0.7942411886073);

    glVertex2f(0.00605517072, 0.7770221457297);
    glVertex2f(0.0099385485388, 0.7727599017822);
    glVertex2f(0.020300945765, 0.8027951760829);
    ///-trunk-
    glVertex2f(-0.0066612043597, 0.7200421063425);
    glVertex2f(0.0100833344103, 0.7200421063425);
    glVertex2f(0.0046809958851, 0.809643879124);
    ///-5-
    ///Branches
    glVertex2f(0.3177792984984, 0.7624732976933);
    glVertex2f(0.3221308496096, 0.7707117495676);
    glVertex2f(0.300944184956, 0.7856129187763);

    glVertex2f(0.3221308496096, 0.7707117495676);
    glVertex2f(0.325, 0.765);
    glVertex2f(0.3314248394714, 0.7852864154872);
    ///-trunk-
    glVertex2f(0.3111470434093, 0.7200421063425);
    glVertex2f(0.3293274266072, 0.7200421063425);
    glVertex2f(0.3203779380671, 0.7986584690995);
    ///-6-
    ///Branches
    glVertex2f(0.3666223607519, 0.7791860987222);
    glVertex2f(0.3702601406883, 0.7889801216277);
    glVertex2f(0.3491679110256, 0.8061978926761);

    glVertex2f(0.3702601406883, 0.7889801216277);
    glVertex2f(0.3775049851365, 0.7852819610519);
    glVertex2f(0.3901280157252, 0.8183621903443);
    ///-trunk-
    glVertex2f(0.3582919377498, 0.7200421063425);
    glVertex2f(0.3842516019819, 0.7200421063425);
    glVertex2f(0.3707627234469, 0.8246142676285);

    glEnd();
}

void Bushes() {
    ///inner
    glColor3f(0.0f, 0.8f, 0.1f);
    drawFilledCircle(0.1436296840026, 0.0242120309861, 0.02);
    drawFilledCircle(0.1626956884299, 0.0441254133879, 0.02);
    drawFilledCircle(0.1902763493926, 0.0615524529981, 0.025);
    drawFilledCircle(0.2194700127245, 0.069123063637, 0.025);
    drawFilledCircle(0.2508229977827, 0.0699704416115, 0.025);
    drawFilledCircle(0.2703126911972, 0.0521755041461, 0.025);
    drawFilledCircle(0.3003946092936, 0.0475149252861, 0.02);
    drawFilledCircle(0.3088683890391, 0.0216698970625, 0.02);
    ///outer
    glColor3f(0.0f, 0.6f, 0.1f);
    drawFilledCircle(0.1614246214681, 0.02, 0.02);
    drawFilledCircle(0.1864222717172, 0.0292962988334, 0.025);
    drawFilledCircle(0.22, 0.04, 0.025);
    drawFilledCircle(0.2571783325918, 0.0390411455406, 0.025);
    drawFilledCircle(0.285565494739, 0.02, 0.02);
    ///outer-base
    glBegin(GL_QUADS);
    glVertex2f(0.2, 0.03);
    glVertex2f(0.2676582912732, 0.0316006076458);
    glVertex2f(0.2860419166476, 0.0);
    glVertex2f(0.1614246214681, 0.0);
    glEnd();

}

///-additional different tree-
void TreeDiff() {

    glColor3f(0.0f, 0.5f, 0.1f);
    drawFilledCircle(-0.121020534451, 0.8204706816194, 0.055);

    glBegin(GL_TRIANGLES);
    glColor3f(0.6f, 0.3f, 0.0f);
    glVertex2f(-0.125160897146, 0.7750425127131);
    glVertex2f(-0.1215231172096, 0.7848365356186);
    glVertex2f(-0.1426153468723, 0.802054306667);

    glVertex2f(-0.1215231172096, 0.7848365356186);
    glVertex2f(-0.1142782727615, 0.7811383750428);
    glVertex2f(-0.1016552421727, 0.8142186043352);

    glVertex2f(-0.1334913201481, 0.716884461922);
    glVertex2f(-0.107531655916, 0.71627837528);
    glVertex2f(-0.121020534451, 0.8204706816194);
    glEnd();
}

void Bborders() {
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    //--------------------- Sun Rays' Borders ---------------------
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0969257264857, 0.9799402491368);
    glVertex2f(0.122071624913, 0.9799402491368);
    glVertex2f(0.122071624913, 0.9696693892158);
    glVertex2f(0.0969257264857, 0.9696693892158);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1004674023205, 0.934606798451);
    glVertex2f(0.1256575895913, 0.9462305447827);
    glVertex2f(0.1303328264589, 0.9364125473608);
    glVertex2f(0.1055438043504, 0.9243359385301);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1447202325101, 0.9214949580941);
    glVertex2f(0.1520083857302, 0.9164932843157);
    glVertex2f(0.1259996820822, 0.8746221295417);
    glVertex2f(0.118425718932, 0.8796238033202);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1714399966131, 0.9119708601186);
    glVertex2f(0.1840980504362, 0.9119708601186);
    glVertex2f(0.1840980504362, 0.8524355480574);
    glVertex2f(0.1714399966131, 0.8524355480574);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1999403586908, 0.9169531425939);
    glVertex2f(0.2095163266537, 0.9222883247447);
    glVertex2f(0.2381074310003, 0.8681157059828);
    glVertex2f(0.2281210644103, 0.8630541229167);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.2218024895332, 0.9384770878313);
    glVertex2f(0.2274170357866, 0.9453935578536);
    glVertex2f(0.2546266622399, 0.9243684681596);
    glVertex2f(0.2496734678922, 0.9172300410114);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.2319489889454, 0.9719378907237);
    glVertex2f(0.2690451346652, 0.9719378907237);
    glVertex2f(0.2690451346652, 0.9621702781253);
    glVertex2f(0.2319489889454, 0.9621702781253);
    glEnd();
    //-------------------- Outer Frame Border  ---------------------
    glLineWidth(2.0f);
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5, 0.9919022083036);
    glVertex2f(0.5, 0.9919022083036);
    glVertex2f(0.5, 0);
    glVertex2f(-0.5, 0);
    glEnd();

}

void h1() {

    glBegin(GL_QUADS);
    //1
    glColor3f(0.9f, 0.6f, 0.2f);
    glVertex2f(-0.4629417989007, 0.6428159477847);
    glVertex2f(-0.3712187980079, 0.6434618844107);
    glVertex2f(-0.3725106712599, 0.555614503274);
    glVertex2f(-0.4630935385123, 0.5545195994008);
    //2
    glVertex2f(-0.1, 0.55);
    glVertex2f(-0.0099249944688, 0.55);
    glVertex2f(-0.0095079523571, 0.5073842409067);
    glVertex2f(-0.1, 0.5073842409067);
    //3
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.4630935385123, 0.555614503274);
    glVertex2f(-0.3725106712599, 0.555614503274);
    glVertex2f(-0.3725106712599, 0.5073842409067);
    glVertex2f(-0.4630935385123, 0.5073842409067);
    //4
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.3712187980079, 0.6434618844107);
    glVertex2f(-0.1880550145568, 0.6434618844107);
    glVertex2f(-0.1880550145568, 0.5073842409067);
    glVertex2f(-0.3712187980079, 0.5073842409067);
    //5
    glColor3f(0.6f, 0.9f, 0.3f);
    glVertex2f(-0.3705528700632, 0.6888869098231);
    glVertex2f(-0.1880550145568, 0.6888869098231);
    glVertex2f(-0.1880550145568, 0.6434618844107);
    glVertex2f(-0.3705528700632, 0.6434618844107);
    //6
    glVertex2f(-0.1, 0.55);
    glVertex2f(-0.1877147686865, 0.55);
    glVertex2f(-0.1877147686865, 0.5073842409067);//
    glVertex2f(-0.1, 0.5073842409067);
    //7
    glColor3f(1.0f, 1.0f, 0.45f);
    glVertex2f(-0.3705528700632, 0.779681999854);
    glVertex2f(-0.1880550145568, 0.7786926400941);
    glVertex2f(-0.1880550145568, 0.6888869098231);
    glVertex2f(-0.3705528700632, 0.6888869098231);
    //8
    glVertex2f(-0.1, 0.55);
    glVertex2f(-0.1880550145568, 0.55);
    glVertex2f(-0.1880550145568, 0.6432169233696);//
    glVertex2f(-0.1, 0.6432169233696);

    ///-windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    ///-10.1-
    glVertex2f(-0.3492463746121, 0.6235057238155);
    glVertex2f(-0.3182443250081, 0.6235057238155);
    glVertex2f(-0.3182443250081, 0.5934337356997);
    glVertex2f(-0.3492463746121, 0.5934337356997);
    ///-11.2-
    glVertex2f(-0.160106086186, 0.5827771815811);
    glVertex2f(-0.1298427226758, 0.5827771815811);
    glVertex2f(-0.1298427226758, 0.5509285915799);
    glVertex2f(-0.160106086186, 0.5509285915799);

    glEnd();

    glBegin(GL_TRIANGLES);
    //1
    glColor3f(0.9f, 0.5f, 0.8f);
    glVertex2f(-0.4629417989007, 0.6434618844107);
    glVertex2f(-0.3712187980079, 0.6434618844107);
    glVertex2f(-0.4177262350803, 0.8133432170502);
    //2
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.3695327005123, 0.779681999854);
    glVertex2f(-0.2807876703671, 0.779681999854);
    glVertex2f(-0.3272165897587, 0.9529670633618);
    //3
    glVertex2f(-0.1017031039734, 0.6422420361975);
    glVertex2f(-0.1, 0.5504092364938);
    glVertex2f(-0.0099249944688, 0.5504092364938);
    //4
    glColor3f(0.9f, 0.6f, 0.2f);
    glVertex2f(-0.2807876703671, 0.779681999854);
    glVertex2f(-0.1909003858981, 0.779681999854);
    glVertex2f(-0.2343839774009, 0.9529670633618);
    //5
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.1900498704132, 0.729750041711);
    glVertex2f(-0.1880550145568, 0.6432169233696);
    glVertex2f(-0.1017031039734, 0.6432169233696);

    glEnd();

    ///-circular windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.4163675956785, 0.5984394220079, 0.02);
    drawFilledSemicircle(-0.2806351808443, 0.5099843657389, 0.05);
    drawFilledSemicircle(-0.2809962211591, 0.6928818780451, 0.05);
    drawFilledCircle(-0.2356644829932, 0.8336976483028, 0.02);
}
void borders1() {
    // Borders
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    /// Quads
    glBegin(GL_LINE_LOOP);
    //1
    glVertex2f(-0.4629417989007, 0.6428159477847);
    glVertex2f(-0.3712187980079, 0.6434618844107);
    glVertex2f(-0.3725106712599, 0.555614503274);
    glVertex2f(-0.4630935385123, 0.5545195994008);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2
    glVertex2f(-0.4630935385123, 0.555614503274);
    glVertex2f(-0.3725106712599, 0.555614503274);
    glVertex2f(-0.3725106712599, 0.5073842409067);
    glVertex2f(-0.4630935385123, 0.5073842409067);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3
    glVertex2f(-0.3712187980079, 0.6434618844107);
    glVertex2f(-0.1880550145568, 0.6434618844107);
    glVertex2f(-0.1880550145568, 0.5073842409067);
    glVertex2f(-0.3712187980079, 0.5073842409067);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //4
    glVertex2f(-0.3492463746121, 0.6235057238155);
    glVertex2f(-0.3182443250081, 0.6235057238155);
    glVertex2f(-0.3182443250081, 0.5934337356997);
    glVertex2f(-0.3492463746121, 0.5934337356997);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5
    glVertex2f(-0.3705528700632, 0.6888869098231);
    glVertex2f(-0.1880550145568, 0.6888869098231);
    glVertex2f(-0.1880550145568, 0.6434618844107);
    glVertex2f(-0.3705528700632, 0.6434618844107);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //6
    glVertex2f(-0.3705528700632, 0.779681999854);
    glVertex2f(-0.1880550145568, 0.7786926400941);
    glVertex2f(-0.1880550145568, 0.6888869098231);
    glVertex2f(-0.3705528700632, 0.6888869098231);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // Square 7
    glVertex2f(-0.1, 0.55);
    glVertex2f(-0.1880550145568, 0.55);
    glVertex2f(-0.1880550145568, 0.6432169233696);//
    glVertex2f(-0.1, 0.6432169233696);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //8
    glVertex2f(-0.160106086186, 0.5827771815811);
    glVertex2f(-0.1298427226758, 0.5827771815811);
    glVertex2f(-0.1298427226758, 0.5509285915799);
    glVertex2f(-0.160106086186, 0.5509285915799);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //9
    glVertex2f(-0.1, 0.55);
    glVertex2f(-0.1877147686865, 0.55);
    glVertex2f(-0.1877147686865, 0.5073842409067);//
    glVertex2f(-0.1, 0.5073842409067);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //10
    glVertex2f(-0.1, 0.55);
    glVertex2f(-0.0099249944688, 0.55);
    glVertex2f(-0.0095079523571, 0.5073842409067);
    glVertex2f(-0.1, 0.5073842409067);
    glEnd();

    ///Triangles
//1
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4629417989007, 0.6434618844107);
    glVertex2f(-0.3712187980079, 0.6434618844107);
    glVertex2f(-0.4177262350803, 0.8133432170502);
    glEnd();
    //2
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3695327005123, 0.779681999854);
    glVertex2f(-0.2807876703671, 0.779681999854);
    glVertex2f(-0.3272165897587, 0.9529670633618);
    glEnd();
    //3
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.2807876703671, 0.779681999854);
    glVertex2f(-0.1909003858981, 0.779681999854);
    glVertex2f(-0.2343839774009, 0.9529670633618);
    glEnd();
    //4
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1900498704132, 0.729750041711);
    glVertex2f(-0.1880550145568, 0.6432169233696);
    glVertex2f(-0.1017031039734, 0.6432169233696);
    glEnd();
    //5
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1017031039734, 0.6422420361975);
    glVertex2f(-0.1, 0.5504092364938);
    glVertex2f(-0.0099249944688, 0.5504092364938);
    glEnd();

    /// Circles
    drawHollowCircle(-0.4163675956785, 0.5984394220079, 0.02);
    drawHollowSemicircle(-0.2806351808443, 0.5099843657389, 0.05);
    drawHollowSemicircle(-0.2809962211591, 0.6928818780451, 0.05);
    drawHollowCircle(-0.2356644829932, 0.8336976483028, 0.02);
}

void h2() {

    glBegin(GL_QUADS);
    //1
    glColor3f(0.9f, 0.6f, 0.2f);
    glVertex2f(-0.3470088672972, 0.4545599694191);
    glVertex2f(-0.2632379336643, 0.4545599694191);
    glVertex2f(-0.2632379336643, 0.4134309929032);
    glVertex2f(-0.3470088672972, 0.4134309929032);
    //2
    glColor3f(0.6f, 0.9f, 0.3f);
    glVertex2f(-0.3470088672972, 0.4134309929032);
    glVertex2f(-0.2624743215828, 0.4134309929032);
    glVertex2f(-0.2624743215828, 0.3259556671007);
    glVertex2f(-0.3470088672972, 0.3259556671007);
    //3
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.262045836957, 0.4134309929032);
    glVertex2f(-0.1781579170517, 0.4134309929032);
    glVertex2f(-0.1781579170517, 0.3259556671007);
    glVertex2f(-0.262045836957, 0.3259556671007);
    //4
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.262045836957, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4134309929032);
    glVertex2f(-0.262045836957, 0.4134309929032);

    ///-windows-
    ///-5.1-
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.3285736019951, 0.4126721726242);
    glVertex2f(-0.2864376290163, 0.4126721726242);
    glVertex2f(-0.2864376290163, 0.3703071997923);
    glVertex2f(-0.3285736019951, 0.3703071997923);
    ///-6.2-
    glVertex2f(-0.2394926591215, 0.4126721726242);
    glVertex2f(-0.1996466846742, 0.4126721726242);
    glVertex2f(-0.1996466846742, 0.3703071997923);
    glVertex2f(-0.2394926591215, 0.3703071997923);

    glEnd();

    glBegin(GL_TRIANGLES);
    //1
    glColor3f(0.2f, 0.9f, 1.0f);
    glVertex2f(-0.262045836957, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4994201978777);
    glVertex2f(-0.2200696275226, 0.6660696663209);
    //2
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.3470088672972, 0.4134309929032);
    glVertex2f(-0.3470088672972, 0.3259556671007);
    glVertex2f(-0.4347811781046, 0.3259556671007);

    glEnd();

    ///-circular windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.2198735519298, 0.4565120375867, 0.02);

}
void borders2() {
    // Borders
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    /// Quads
    glBegin(GL_LINE_LOOP);
    //1
    glVertex2f(-0.3470088672972, 0.4545599694191);
    glVertex2f(-0.2632379336643, 0.4545599694191);
    glVertex2f(-0.2632379336643, 0.4134309929032);
    glVertex2f(-0.3470088672972, 0.4134309929032);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2
    glVertex2f(-0.3470088672972, 0.4134309929032);
    glVertex2f(-0.2624743215828, 0.4134309929032);
    glVertex2f(-0.2624743215828, 0.3259556671007);
    glVertex2f(-0.3470088672972, 0.3259556671007);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3
    glVertex2f(-0.3285736019951, 0.4126721726242);
    glVertex2f(-0.2864376290163, 0.4126721726242);
    glVertex2f(-0.2864376290163, 0.3703071997923);
    glVertex2f(-0.3285736019951, 0.3703071997923);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //4
    glVertex2f(-0.262045836957, 0.4134309929032);
    glVertex2f(-0.1781579170517, 0.4134309929032);
    glVertex2f(-0.1781579170517, 0.3259556671007);
    glVertex2f(-0.262045836957, 0.3259556671007);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5
    glVertex2f(-0.2394926591215, 0.4126721726242);
    glVertex2f(-0.1996466846742, 0.4126721726242);
    glVertex2f(-0.1996466846742, 0.3703071997923);
    glVertex2f(-0.2394926591215, 0.3703071997923);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //6
    glVertex2f(-0.262045836957, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4134309929032);
    glVertex2f(-0.262045836957, 0.4134309929032);
    glEnd();

    /// Triangles
//1
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.262045836957, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4994201978777);
    glVertex2f(-0.2200696275226, 0.6660696663209);
    glEnd();
    //2
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3470088672972, 0.4134309929032);
    glVertex2f(-0.3470088672972, 0.3259556671007);
    glVertex2f(-0.4347811781046, 0.3259556671007);
    glEnd();

    /// Circles
    drawHollowCircle(-0.2198735519298, 0.4565120375867, 0.02);
}

void h3() {

    glBegin(GL_QUADS);
    //1
    glColor3f(1.0f, 1.0f, 0.45f);
    glVertex2f(-0.4609258069856, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.1427250830332);
    glVertex2f(-0.4609258069856, 0.1427250830332);
    //4
    glVertex2f(-0.322409035816, 0.1427250830332);
    glVertex2f(-0.2307069369642, 0.1427250830332);
    glVertex2f(-0.2307069369642, 0.0544963232281);
    glVertex2f(-0.322409035816, 0.0544963232281);
    //7
    glVertex2f(-0.0065819183189, 0.1478695012057);
    glVertex2f(0.0816007705309, 0.1478695012057);
    glVertex2f(0.0816007705309, 0.0550156160384);
    glVertex2f(-0.0065819183189, 0.0550156160384);
    //9
    glVertex2f(-0.0953314416441, 0.4544899508711);
    glVertex2f(-0.0123184816386, 0.4544899508711);
    glVertex2f(-0.0123184816386, 0.3693158932092);
    glVertex2f(-0.0953314416441, 0.3693158932092);
    //2
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.4609258069856, 0.1427250830332);
    glVertex2f(-0.3708392774278, 0.1427250830332);
    glVertex2f(-0.3708392774278, 0.0546916565721);
    glVertex2f(-0.4609258069856, 0.0546916565721);
    //3
    glColor3f(0.9f, 0.5f, 0.8f);
    glVertex2f(-0.3704622446258, 0.1427250830332);
    glVertex2f(-0.322409035816, 0.1427250830332);
    glVertex2f(-0.322409035816, 0.0560542016588);
    glVertex2f(-0.3704622446258, 0.0560542016588);
    glVertex2f(-0.0065819183189, 0.1936650971883);
    //8
    glVertex2f(0.0816007705309, 0.1936650971883);
    glVertex2f(0.0816007705309, 0.1478695012057);
    glVertex2f(-0.0065819183189, 0.1478695012057);
    //5
    glColor3f(0.6f, 0.9f, 0.3f);
    glVertex2f(-0.2307069369642, 0.1452306562782);
    glVertex2f(-0.1889507835909, 0.1458918578259);
    glVertex2f(-0.1889507835909, 0.0544963232281);
    glVertex2f(-0.2307069369642, 0.0544963232281);
    //6
    glColor3f(0.9f, 0.6f, 0.2f);
    glVertex2f(-0.1871040795168, 0.1936650971883);
    glVertex2f(-0.0092754712566, 0.1936650971883);
    glVertex2f(-0.0092754712566, 0.0560542016588);
    glVertex2f(-0.1871040795168, 0.0560542016588);

    ///-windows-
    ///-10.1-
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.4372445471994, 0.1889148777583);
    glVertex2f(-0.3935332204485, 0.1889148777583);
    glVertex2f(-0.3935332204485, 0.1428075276637);
    glVertex2f(-0.4372445471994, 0.1428075276637);
    ///-11.2-
    glVertex2f(-0.4386357266327, 0.0964494630358);
    glVertex2f(-0.3930893138333, 0.0964494630358);
    glVertex2f(-0.3930893138333, 0.0546348676661);
    glVertex2f(-0.4386357266327, 0.0546348676661);
    ///-12.3-
    glVertex2f(-0.3003061937678, 0.1474578324959);
    glVertex2f(-0.2566837276871, 0.1474578324959);
    glVertex2f(-0.2566837276871, 0.1022079178479);
    glVertex2f(-0.3003061937678, 0.1022079178479);
    ///-13.4-
    glVertex2f(-0.1719955529426, 0.1673999198162);
    glVertex2f(-0.1422924397696, 0.1673999198162);
    glVertex2f(-0.1422924397696, 0.1382089292841);
    glVertex2f(-0.1719955529426, 0.1382089292841);
    ///-14.5-
    glVertex2f(0.0159534562729, 0.1448665236159);
    glVertex2f(0.0589717581097, 0.1448665236159);
    glVertex2f(0.0589717581097, 0.102872467061);
    glVertex2f(0.0159534562729, 0.102872467061);
    ///-15.6-
    glVertex2f(-0.0745058571676, 0.4526719547753);
    glVertex2f(-0.0328245148573, 0.4526719547753);
    glVertex2f(-0.0328245148573, 0.4119251717096);
    glVertex2f(-0.0745058571676, 0.4119251717096);

    glEnd();

    glBegin(GL_TRIANGLES);
    //1
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(-0.4609258069856, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.2358691375429);
    glVertex2f(-0.4152297412679, 0.4082085853926);
    //2
    glVertex2f(-0.3421421626042, 0.148488321877);
    glVertex2f(-0.2134857894445, 0.148488321877);
    glVertex2f(-0.278788439758, 0.2113227519129);
    //3
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(-0.1871040795168, 0.1936650971883);
    glVertex2f(-0.0999002253078, 0.1936650971883);
    glVertex2f(-0.1451585360614, 0.3676582757371);
    //4
    glVertex2f(-0.0999002253078, 0.1936650971883);
    glVertex2f(-0.0090655261498, 0.1936650971883);
    glVertex2f(-0.0529689337686, 0.3676582757371);
    //5
    glVertex2f(-0.0090655261498, 0.1936650971883);
    glVertex2f(0.0799722257501, 0.1936650971883);
    glVertex2f(0.0371000794033, 0.3676582757371);
    //6
    glColor3f(0.2f, 0.9f, 1.0f);
    glVertex2f(-0.1451585360614, 0.3676582757371);
    glVertex2f(-0.0529689337686, 0.3676582757371);
    glVertex2f(-0.0999002253078, 0.1936650971883);
    //7
    glVertex2f(-0.0529689337686, 0.3676582757371);
    glVertex2f(0.0371000794033, 0.3676582757371);
    glVertex2f(-0.0090655261498, 0.1936650971883);
    //8
    glVertex2f(-0.111519768402, 0.4572917766561);
    glVertex2f(0.0039777167361, 0.4572917766561);
    glVertex2f(-0.0533040548688, 0.5229790256161);

    glEnd();

    ///-circular windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledSemicircle(-0.102660891235, 0.0526150095881, 0.05);
}
void borders3() {
    // Borders
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    /// Quads
    glBegin(GL_LINE_LOOP);
    //1
    glVertex2f(-0.4609258069856, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.1427250830332);
    glVertex2f(-0.4609258069856, 0.1427250830332);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2
    glVertex2f(-0.4609258069856, 0.1427250830332);
    glVertex2f(-0.3708392774278, 0.1427250830332);
    glVertex2f(-0.3708392774278, 0.0546916565721);
    glVertex2f(-0.4609258069856, 0.0546916565721);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3
    glVertex2f(-0.3704622446258, 0.1427250830332);
    glVertex2f(-0.322409035816, 0.1427250830332);
    glVertex2f(-0.322409035816, 0.0560542016588);
    glVertex2f(-0.3704622446258, 0.0560542016588);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //4
    glVertex2f(-0.322409035816, 0.1427250830332);
    glVertex2f(-0.2307069369642, 0.1427250830332);
    glVertex2f(-0.2307069369642, 0.0544963232281);
    glVertex2f(-0.322409035816, 0.0544963232281);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5
    glVertex2f(-0.2307069369642, 0.1452306562782);
    glVertex2f(-0.1889507835909, 0.1458918578259);
    glVertex2f(-0.1889507835909, 0.0544963232281);
    glVertex2f(-0.2307069369642, 0.0544963232281);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //6
    glVertex2f(-0.1871040795168, 0.1936650971883);
    glVertex2f(-0.0092754712566, 0.1936650971883);
    glVertex2f(-0.0092754712566, 0.0560542016588);
    glVertex2f(-0.1871040795168, 0.0560542016588);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //7
    glVertex2f(-0.0065819183189, 0.1478695012057);
    glVertex2f(0.0816007705309, 0.1478695012057);
    glVertex2f(0.0816007705309, 0.0550156160384);
    glVertex2f(-0.0065819183189, 0.0550156160384);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //8
    glVertex2f(-0.0065819183189, 0.1936650971883);
    glVertex2f(0.0816007705309, 0.1936650971883);
    glVertex2f(0.0816007705309, 0.1478695012057);
    glVertex2f(-0.0065819183189, 0.1478695012057);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //9
    glVertex2f(-0.0953314416441, 0.4544899508711);
    glVertex2f(-0.0123184816386, 0.4544899508711);
    glVertex2f(-0.0123184816386, 0.3693158932092);
    glVertex2f(-0.0953314416441, 0.3693158932092);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //10
    glVertex2f(-0.4372445471994, 0.1889148777583);
    glVertex2f(-0.3935332204485, 0.1889148777583);
    glVertex2f(-0.3935332204485, 0.1428075276637);
    glVertex2f(-0.4372445471994, 0.1428075276637);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //11
    glVertex2f(-0.4386357266327, 0.0964494630358);
    glVertex2f(-0.3930893138333, 0.0964494630358);
    glVertex2f(-0.3930893138333, 0.0546348676661);
    glVertex2f(-0.4386357266327, 0.0546348676661);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //12
    glVertex2f(-0.3003061937678, 0.1474578324959);
    glVertex2f(-0.2566837276871, 0.1474578324959);
    glVertex2f(-0.2566837276871, 0.1022079178479);
    glVertex2f(-0.3003061937678, 0.1022079178479);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //13
    glVertex2f(-0.1719955529426, 0.1673999198162);
    glVertex2f(-0.1422924397696, 0.1673999198162);
    glVertex2f(-0.1422924397696, 0.1382089292841);
    glVertex2f(-0.1719955529426, 0.1382089292841);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //14
    glVertex2f(0.0159534562729, 0.1448665236159);
    glVertex2f(0.0589717581097, 0.1448665236159);
    glVertex2f(0.0589717581097, 0.102872467061);
    glVertex2f(0.0159534562729, 0.102872467061);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //15
    glVertex2f(-0.0745058571676, 0.4526719547753);
    glVertex2f(-0.0328245148573, 0.4526719547753);
    glVertex2f(-0.0328245148573, 0.4119251717096);
    glVertex2f(-0.0745058571676, 0.4119251717096);

    glEnd();

    /// Triangles
//1
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4609258069856, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.2358691375429);
    glVertex2f(-0.4152297412679, 0.4082085853926);
    glEnd();
    //2
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.3421421626042, 0.148488321877);
    glVertex2f(-0.2134857894445, 0.148488321877);
    glVertex2f(-0.278788439758, 0.2113227519129);
    glEnd();
    //3
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1871040795168, 0.1936650971883);
    glVertex2f(-0.0999002253078, 0.1936650971883);
    glVertex2f(-0.1451585360614, 0.3676582757371);
    glEnd();
    //4
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.0999002253078, 0.1936650971883);
    glVertex2f(-0.0090655261498, 0.1936650971883);
    glVertex2f(-0.0529689337686, 0.3676582757371);
    glEnd();
    //5
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.0090655261498, 0.1936650971883);
    glVertex2f(0.0799722257501, 0.1936650971883);
    glVertex2f(0.0371000794033, 0.3676582757371);
    glEnd();
    //6
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.1451585360614, 0.3676582757371);
    glVertex2f(-0.0529689337686, 0.3676582757371);
    glVertex2f(-0.0999002253078, 0.1936650971883);
    glEnd();
    //7
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.0529689337686, 0.3676582757371);
    glVertex2f(0.0371000794033, 0.3676582757371);
    glVertex2f(-0.0090655261498, 0.1936650971883);
    glEnd();
    //8
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.111519768402, 0.4572917766561);
    glVertex2f(0.0039777167361, 0.4572917766561);
    glVertex2f(-0.0533040548688, 0.5229790256161);
    glEnd();

    /// Circle
    drawHollowSemicircle(-0.102660891235, 0.0526150095881, 0.05);
}


void h4() {

    glBegin(GL_QUADS);
    //1
    glColor3f(0.6f, 0.9f, 0.3f);
    glVertex2f(-0.0442362499105, 0.6870579303355);
    glVertex2f(0.000598228064, 0.6870579303355);
    glVertex2f(0.000598228064, 0.6074349628415);
    glVertex2f(-0.0442362499105, 0.6074349628415);
    //2
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(0.000598228064, 0.7357921570449);
    glVertex2f(0.3035508823627, 0.7357921570449);
    glVertex2f(0.3035508823627, 0.6074349628415);
    glVertex2f(0.000598228064, 0.6074349628415);
    //3
    glColor3f(0.2f, 0.9f, 1.0f);
    glVertex2f(0.000598228064, 0.78);
    glVertex2f(0.3035508823627, 0.78);
    glVertex2f(0.3035508823627, 0.7357921570449);
    glVertex2f(0.000598228064, 0.7357921570449);

    ///-windows-
    ///-4.1-
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0398789611984, 0.7341153271998);
    glVertex2f(0.0870158409596, 0.7341153271998);
    glVertex2f(0.0870158409596, 0.6452426684833);
    glVertex2f(0.0398789611984, 0.6452426684833);
    ///-5.2-
    glVertex2f(0.1297336382432, 0.7341153271998);
    glVertex2f(0.1749064813477, 0.7341153271998);
    glVertex2f(0.1749064813477, 0.6452426684833);
    glVertex2f(0.1297336382432, 0.6452426684833);
    ///-6.3-
    glVertex2f(0.2176242786313, 0.7341153271998);
    glVertex2f(0.2637791400642, 0.7341153271998);
    glVertex2f(0.2637791400642, 0.6452426684833);
    glVertex2f(0.2176242786313, 0.6452426684833);

    glEnd();

    glBegin(GL_TRIANGLES);
    //1
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(0.000598228064, 0.78);
    glVertex2f(0.3035508823627, 0.78);
    glVertex2f(0.1518290506313, 0.8671788106924);

    glEnd();

    ///-circular windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.1509205310369, 0.8236263300851, 0.02);

}
void borders4() {
    // Borders
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    /// Quads
    glBegin(GL_LINE_LOOP);
    //1
    glVertex2f(-0.0442362499105, 0.6870579303355);
    glVertex2f(0.000598228064, 0.6870579303355);
    glVertex2f(0.000598228064, 0.6074349628415);
    glVertex2f(-0.0442362499105, 0.6074349628415);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2
    glVertex2f(0.000598228064, 0.7357921570449);
    glVertex2f(0.3035508823627, 0.7357921570449);
    glVertex2f(0.3035508823627, 0.6074349628415);
    glVertex2f(0.000598228064, 0.6074349628415);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3
    glVertex2f(0.000598228064, 0.78);
    glVertex2f(0.3035508823627, 0.78);
    glVertex2f(0.3035508823627, 0.7357921570449);
    glVertex2f(0.000598228064, 0.7357921570449);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //4
    glVertex2f(0.0398789611984, 0.7341153271998);
    glVertex2f(0.0870158409596, 0.7341153271998);
    glVertex2f(0.0870158409596, 0.6452426684833);
    glVertex2f(0.0398789611984, 0.6452426684833);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5
    glVertex2f(0.1297336382432, 0.7341153271998);
    glVertex2f(0.1749064813477, 0.7341153271998);
    glVertex2f(0.1749064813477, 0.6452426684833);
    glVertex2f(0.1297336382432, 0.6452426684833);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //6
    glVertex2f(0.2176242786313, 0.7341153271998);
    glVertex2f(0.2637791400642, 0.7341153271998);
    glVertex2f(0.2637791400642, 0.6452426684833);
    glVertex2f(0.2176242786313, 0.6452426684833);
    glEnd();

    /// Triangles
//1
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.000598228064, 0.78);
    glVertex2f(0.3035508823627, 0.78);
    glVertex2f(0.1518290506313, 0.8671788106924);
    glEnd();

    /// Circle
    drawHollowCircle(0.1509205310369, 0.8236263300851, 0.02);
}

void h5() {
    glBegin(GL_QUADS);
    //1
    glColor3f(1.0f, 1.0f, 0.45f);
    glVertex2f(0.1239281518482, 0.4984790893068);
    glVertex2f(0.2141915111006, 0.4984790893068);
    glVertex2f(0.2141915111006, 0.4046961027389);
    glVertex2f(0.1239281518482, 0.4046961027389);
    //2
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(0.1239281518482, 0.4046961027389);
    glVertex2f(0.2141915111006, 0.4046961027389);
    glVertex2f(0.2141915111006, 0.3111921558458);
    glVertex2f(0.1239281518482, 0.3111921558458);
    //3
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(0.2141915111006, 0.4046961027389);
    glVertex2f(0.3016908134545, 0.4046961027389);
    glVertex2f(0.3016908134545, 0.3111921558458);
    glVertex2f(0.2141915111006, 0.3111921558458);
    //4
    glColor3f(0.9f, 0.5f, 0.8f);
    glVertex2f(0.2141915111006, 0.445);
    glVertex2f(0.3016908134545, 0.445);
    glVertex2f(0.3016908134545, 0.4046961027389);
    glVertex2f(0.2141915111006, 0.4046961027389);
    //5
    glColor3f(0.9f, 0.6f, 0.2f);
    glVertex2f(0.3016908134545, 0.445);
    glVertex2f(0.4800906149414, 0.445);
    glVertex2f(0.4800906149414, 0.3094093519816);
    glVertex2f(0.3016908134545, 0.3094093519816);
    //6
    glColor3f(1.0f, 1.0f, 0.45f);
    glVertex2f(0.346690133679, 0.712209501874);
    glVertex2f(0.4341052880775, 0.712209501874);
    glVertex2f(0.4341052880775, 0.6240375063119);
    glVertex2f(0.346690133679, 0.6240375063119);

    ///-windows-
    ///-7.1-
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.1448442509434, 0.4954525841527);
    glVertex2f(0.1909206184304, 0.4954525841527);
    glVertex2f(0.1909206184304, 0.4521687237861);
    glVertex2f(0.1448442509434, 0.4521687237861);
    ///-8.2-
    glVertex2f(0.1478736795413, 0.3994314020184);
    glVertex2f(0.1886730038498, 0.3994314020184);
    glVertex2f(0.1886730038498, 0.35863207771);
    glVertex2f(0.1478736795413, 0.35863207771);
    ///-9.3-
    glVertex2f(0.2360661502106, 0.4000419242049);
    glVertex2f(0.28, 0.4000419242049);
    glVertex2f(0.28, 0.36);
    glVertex2f(0.2360661502106, 0.36);
    ///-10.4-
    glVertex2f(0.4339866224332, 0.4295172614804);
    glVertex2f(0.4645178373426, 0.4295172614804);
    glVertex2f(0.4645178373426, 0.4003490472366);
    glVertex2f(0.4339866224332, 0.4003490472366);

    glEnd();

    glBegin(GL_TRIANGLES);
    //1
    glColor3f(0.6f, 0.9f, 0.3f);
    glVertex2f(0.1239281518482, 0.4984790893068);
    glVertex2f(0.2111439034604, 0.4984790893068);
    glVertex2f(0.1687172687501, 0.673903130506);
    //4
    glVertex2f(0.3463117130972, 0.6232806651483);
    glVertex2f(0.4341052880775, 0.6232806651483);
    glVertex2f(0.3896769121329, 0.4432391784611);
    //2
    glColor3f(0.4f, 0.7f, 0.2f);
    glVertex2f(0.3015916488925, 0.4432391784611);
    glVertex2f(0.3896769121329, 0.4432391784611);
    glVertex2f(0.3463117130972, 0.6232806651483);
    //3
    glVertex2f(0.3896769121329, 0.4432391784611);
    glVertex2f(0.4770156900917, 0.4432391784611);
    glVertex2f(0.4341052880775, 0.6232806651483);
    //5
    glColor3f(0.9f, 0.5f, 0.8f);
    glVertex2f(0.3293274266072, 0.7129673572027);
    glVertex2f(0.4528380425049, 0.7129673572027);
    glVertex2f(0.392515492475, 0.7775704295862);

    glEnd();

    ///-circular windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledSemicircle(0.3864028329709, 0.3094235874811, 0.05);
}
void borders5() {
    // Borders
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    /// Quads
    glBegin(GL_LINE_LOOP);
    //1
    glVertex2f(0.1239281518482, 0.4984790893068);
    glVertex2f(0.2141915111006, 0.4984790893068);
    glVertex2f(0.2141915111006, 0.4046961027389);
    glVertex2f(0.1239281518482, 0.4046961027389);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2
    glVertex2f(0.1239281518482, 0.4046961027389);
    glVertex2f(0.2141915111006, 0.4046961027389);
    glVertex2f(0.2141915111006, 0.3111921558458);
    glVertex2f(0.1239281518482, 0.3111921558458);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3
    glVertex2f(0.2141915111006, 0.4046961027389);
    glVertex2f(0.3016908134545, 0.4046961027389);
    glVertex2f(0.3016908134545, 0.3111921558458);
    glVertex2f(0.2141915111006, 0.3111921558458);
    glEnd();

    glBegin(GL_LINE_LOOP);
    // Square 4
    glVertex2f(0.2141915111006, 0.445);
    glVertex2f(0.3016908134545, 0.445);
    glVertex2f(0.3016908134545, 0.4046961027389);
    glVertex2f(0.2141915111006, 0.4046961027389);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5
    glVertex2f(0.3016908134545, 0.445);
    glVertex2f(0.4800906149414, 0.445);
    glVertex2f(0.4800906149414, 0.3094093519816);
    glVertex2f(0.3016908134545, 0.3094093519816);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //6
    glVertex2f(0.346690133679, 0.712209501874);
    glVertex2f(0.4341052880775, 0.712209501874);
    glVertex2f(0.4341052880775, 0.6240375063119);
    glVertex2f(0.346690133679, 0.6240375063119);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //7
    glVertex2f(0.1448442509434, 0.4954525841527);
    glVertex2f(0.1909206184304, 0.4954525841527);
    glVertex2f(0.1909206184304, 0.4521687237861);
    glVertex2f(0.1448442509434, 0.4521687237861);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //8
    glVertex2f(0.1478736795413, 0.3994314020184);
    glVertex2f(0.1886730038498, 0.3994314020184);
    glVertex2f(0.1886730038498, 0.35863207771);
    glVertex2f(0.1478736795413, 0.35863207771);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //9
    glVertex2f(0.2360661502106, 0.4000419242049);
    glVertex2f(0.28, 0.4000419242049);
    glVertex2f(0.28, 0.36);
    glVertex2f(0.2360661502106, 0.36);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //10
    glVertex2f(0.4339866224332, 0.4295172614804);
    glVertex2f(0.4645178373426, 0.4295172614804);
    glVertex2f(0.4645178373426, 0.4003490472366);
    glVertex2f(0.4339866224332, 0.4003490472366);
    glEnd();

    /// Triangles
//1
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.1239281518482, 0.4984790893068);
    glVertex2f(0.2111439034604, 0.4984790893068);
    glVertex2f(0.1687172687501, 0.673903130506);
    glEnd();
    //2
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.3015916488925, 0.4432391784611);
    glVertex2f(0.3896769121329, 0.4432391784611);
    glVertex2f(0.3463117130972, 0.6232806651483);
    glEnd();
    //3
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.3896769121329, 0.4432391784611);
    glVertex2f(0.4770156900917, 0.4432391784611);
    glVertex2f(0.4341052880775, 0.6232806651483);
    glEnd();
    //4
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.3463117130972, 0.6232806651483);
    glVertex2f(0.4341052880775, 0.6232806651483);
    glVertex2f(0.3896769121329, 0.4432391784611);
    glEnd();
    //5
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.3293274266072, 0.7129673572027);
    glVertex2f(0.4528380425049, 0.7129673572027);
    glVertex2f(0.392515492475, 0.7775704295862);
    glEnd();

    /// circle
    drawHollowSemicircle(0.3864028329709, 0.3094235874811, 0.05);
}

void h6() {

    glBegin(GL_QUADS);
    //1
    glColor3f(0.9f, 0.0f, 0.0f);
    glVertex2f(0.2419209386575, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.1461510824062);
    glVertex2f(0.2419209386575, 0.1461510824062);
    //4
    glVertex2f(0.331061891337, 0.1461510824062);
    glVertex2f(0.4220042010305, 0.1461510824062);
    glVertex2f(0.4220042010305, 0.0547292302115);
    glVertex2f(0.331061891337, 0.0547292302115);
    //2
    glColor3f(0.9f, 0.6f, 0.2f);
    glVertex2f(0.2419066966347, 0.1461510824062);
    glVertex2f(0.331061891337, 0.1461510824062);
    glVertex2f(0.331061891337, 0.0547292302115);
    glVertex2f(0.2419066966347, 0.0547292302115);
    //3
    glColor3f(1.0f, 1.0f, 0.45f);
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.4220042010305, 0.2384253283526);
    glVertex2f(0.4220042010305, 0.1461510824062);
    glVertex2f(0.3318174438345, 0.1461510824062);
    //5
    glColor3f(0.6f, 0.9f, 0.3f);
    glVertex2f(0.4220042010305, 0.1461510824062);
    glVertex2f(0.465550235888, 0.1461510824062);
    glVertex2f(0.465550235888, 0.0547292302115);
    glVertex2f(0.4220042010305, 0.0547292302115);
    ///-windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    ///-7.1-
    glVertex2f(0.2653288240565, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1033773103765);
    glVertex2f(0.2653288240565, 0.1033773103765);
    ///-9.2-
    glVertex2f(0.3560629074801, 0.1470377043847);
    glVertex2f(0.399068098926, 0.1470377043847);
    glVertex2f(0.399068098926, 0.1040325129389);
    glVertex2f(0.3560629074801, 0.1040325129389);

    glEnd();

    glBegin(GL_TRIANGLES);
    //1
    glColor3f(0.1f, 0.4f, 0.9f);
    glVertex2f(0.2419209386575, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.3316219397794, 0.3265885980267);
    //2
    glColor3f(0.9f, 0.5f, 0.8f);
    glVertex2f(0.4197852094534, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.3316219397794, 0.3265885980267);
    glEnd();
}
void borders6() {
    // Borders
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    /// Quads
    glBegin(GL_LINE_LOOP);
    //1
    glVertex2f(0.2419209386575, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.1461510824062);
    glVertex2f(0.2419209386575, 0.1461510824062);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //2
    glVertex2f(0.2419066966347, 0.1461510824062);
    glVertex2f(0.331061891337, 0.1461510824062);
    glVertex2f(0.331061891337, 0.0547292302115);
    glVertex2f(0.2419066966347, 0.0547292302115);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //3
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.4220042010305, 0.2384253283526);
    glVertex2f(0.4220042010305, 0.1461510824062);
    glVertex2f(0.3318174438345, 0.1461510824062);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //4
    glVertex2f(0.331061891337, 0.1461510824062);
    glVertex2f(0.4220042010305, 0.1461510824062);
    glVertex2f(0.4220042010305, 0.0547292302115);
    glVertex2f(0.331061891337, 0.0547292302115);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //5
    glVertex2f(0.4220042010305, 0.1461510824062);
    glVertex2f(0.465550235888, 0.1461510824062);
    glVertex2f(0.465550235888, 0.0547292302115);
    glVertex2f(0.4220042010305, 0.0547292302115);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //7
    glVertex2f(0.2653288240565, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1033773103765);
    glVertex2f(0.2653288240565, 0.1033773103765);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //9
    glVertex2f(0.3560629074801, 0.1470377043847);
    glVertex2f(0.399068098926, 0.1470377043847);
    glVertex2f(0.399068098926, 0.1040325129389);
    glVertex2f(0.3560629074801, 0.1040325129389);
    glEnd();

    /// Triangles
//1
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.2419209386575, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.3316219397794, 0.3265885980267);
    glEnd();
    //2
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.4197852094534, 0.2384253283526);
    glVertex2f(0.3318174438345, 0.2384253283526);
    glVertex2f(0.3316219397794, 0.3265885980267);
    glEnd();
}

void MainDrawing() {
    ground();
    Background();
    Bborders();
    h1();
    borders1();
    h2();
    borders2();
    h3();
    borders3();
    h4();
    borders4();
    h5();
    borders5();
    h6();
    borders6();
}

//---------------------------
/// The Differences Drawing Functions
//---------------------------
void windows() {
    // -h5,h6's different windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    //6
    glVertex2f(0.2653288240565, 0.1877064697675);
    glVertex2f(0.3068202051227, 0.1877064697675);
    glVertex2f(0.3068202051227, 0.1444589709096);
    glVertex2f(0.2653288240565, 0.1444589709096);
    //8
    glVertex2f(0.3560629074801, 0.1881315539886);
    glVertex2f(0.3985902634655, 0.1881315539886);
    glVertex2f(0.3985902634655, 0.1470377043847);
    glVertex2f(0.3560629074801, 0.1470377043847);
    //11
    glVertex2f(0.3697573194177, 0.6882872320267);
    glVertex2f(0.4123713848172, 0.6882872320267);
    glVertex2f(0.4123713848172, 0.6462490323758);
    glVertex2f(0.3697573194177, 0.6462490323758);
    glEnd();
    //---------------------- Borders ----------------------
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    //6
    glVertex2f(0.2653288240565, 0.1877064697675);
    glVertex2f(0.3068202051227, 0.1877064697675);
    glVertex2f(0.3068202051227, 0.1444589709096);
    glVertex2f(0.2653288240565, 0.1444589709096);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //8
    glVertex2f(0.3560629074801, 0.1881315539886);
    glVertex2f(0.3985902634655, 0.1881315539886);
    glVertex2f(0.3985902634655, 0.1470377043847);
    glVertex2f(0.3560629074801, 0.1470377043847);
    glEnd();

    glBegin(GL_LINE_LOOP);
    //11
    glVertex2f(0.3697573194177, 0.6882872320267);
    glVertex2f(0.4123713848172, 0.6882872320267);
    glVertex2f(0.4123713848172, 0.6462490323758);
    glVertex2f(0.3697573194177, 0.6462490323758);
    glEnd();
}
void windowsDiff() {
    // -h6's different windows-
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.2653288240565, 0.235);
    glVertex2f(0.3068202051227, 0.235);
    glVertex2f(0.3068202051227, 0.185);
    glVertex2f(0.2653288240565, 0.185);

    glVertex2f(0.3560629074801, 0.235);
    glVertex2f(0.3985902634655, 0.235);
    glVertex2f(0.3985902634655, 0.185);
    glVertex2f(0.3560629074801, 0.185);
    glEnd();
    //---------------------- Borders ----------------------
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.2653288240565, 0.235);
    glVertex2f(0.3068202051227, 0.235);
    glVertex2f(0.3068202051227, 0.185);
    glVertex2f(0.2653288240565, 0.185);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.3560629074801, 0.235);
    glVertex2f(0.3985902634655, 0.235);
    glVertex2f(0.3985902634655, 0.185);
    glVertex2f(0.3560629074801, 0.185);
    glEnd();

}

void BushesDiff() {
    ///inner
    glColor3f(0.0f, 0.6f, 0.1f);
    drawFilledCircle(0.1436296840026, 0.0242120309861, 0.02);
    drawFilledCircle(0.1626956884299, 0.0441254133879, 0.02);
    drawFilledCircle(0.1902763493926, 0.0615524529981, 0.025);
    drawFilledCircle(0.2194700127245, 0.069123063637, 0.025);
    drawFilledCircle(0.2508229977827, 0.0699704416115, 0.025);
    drawFilledCircle(0.2703126911972, 0.0521755041461, 0.025);
    drawFilledCircle(0.3003946092936, 0.0475149252861, 0.02);
    drawFilledCircle(0.3088683890391, 0.0216698970625, 0.02);
    ///outer
    glColor3f(0.0f, 0.8f, 0.1f);
    drawFilledCircle(0.1614246214681, 0.02, 0.02);
    drawFilledCircle(0.1864222717172, 0.0292962988334, 0.025);
    drawFilledCircle(0.22, 0.04, 0.025);
    drawFilledCircle(0.2571783325918, 0.0390411455406, 0.025);
    drawFilledCircle(0.285565494739, 0.02, 0.02);
    ///outer-base
    glBegin(GL_QUADS);
    glVertex2f(0.2, 0.03);
    glVertex2f(0.2676582912732, 0.0316006076458);
    glVertex2f(0.2860419166476, 0.0);
    glVertex2f(0.1614246214681, 0.0);
    glEnd();
}

void diffrences() {

    ///-difference on h5's window-
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.3903511782622, 0.6677869880377, 0.025);
    ///-additional different cloud-
    glColor3f(0.89f, 0.88f, 0.86f);
    drawFilledCircle(-0.0700084216718, 0.901363446147, 0.008);
    drawFilledCircle(-0.0673887049306, 0.9061622261092, 0.009);
    drawFilledCircle(-0.0663887049306, 0.911100842657, 0.01);
    drawFilledCircle(-0.05, 0.915, 0.015);
    drawFilledCircle(-0.0256652743113, 0.901363446147, 0.01);
    drawFilledCircle(-0.0325058114949, 0.9061622261092, 0.009);
    drawFilledCircle(-0.0335058114949, 0.9137038914799, 0.008);

    glBegin(GL_QUADS);
    //-cloud's base-
    glVertex2f(-0.0597731995463, 0.908808640147);
    glVertex2f(-0.0332712851143, 0.9083517105878);
    glVertex2f(-0.0210255729285, 0.8945524379008);
    glVertex2f(-0.0707395089664, 0.8945524379008);
    ///-difference on h6's color-
    glColor3f(1.0f, 1.0f, 0.45f);
    glVertex2f(0.2419066966347, 0.1461510824062);
    glVertex2f(0.331061891337, 0.1461510824062);
    glVertex2f(0.331061891337, 0.0547292302115);
    glVertex2f(0.2419066966347, 0.0547292302115);
    // - h6's window -
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.2653288240565, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1033773103765);
    glVertex2f(0.2653288240565, 0.1033773103765);
    glEnd();

    glBegin(GL_TRIANGLES);
    ///-difference on h2's triangle color-
    glColor3f(0.9f, 0.5f, 0.8f);
    glVertex2f(-0.262045836957, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4994201978777);
    glVertex2f(-0.2200696275226, 0.6660696663209);
    ///-difference on h3's triangle color-
    glColor3f(0.6f, 0.9f, 0.3f);
    glVertex2f(-0.4609258069856, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.2358691375429);
    glVertex2f(-0.4152297412679, 0.4082085853926);
    glEnd();
    //---------------------- Borders ----------------------
    glLineWidth(1.0f);
    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.2653288240565, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1444589709096);
    glVertex2f(0.3068202051227, 0.1033773103765);
    glVertex2f(0.2653288240565, 0.1033773103765);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.262045836957, 0.4994201978777);
    glVertex2f(-0.1781579170517, 0.4994201978777);
    glVertex2f(-0.2200696275226, 0.6660696663209);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.4609258069856, 0.2358691375429);
    glVertex2f(-0.3708392774278, 0.2358691375429);
    glVertex2f(-0.4152297412679, 0.4082085853926);
    glEnd();

    drawHollowCircle(0.3903511782622, 0.6677869880377, 0.025);
    ///--------------------------------------------------------
    ///calling other differences functions
    BushesDiff();
    windowsDiff();
}

void diffrenceCircles() {
    glLineWidth(2.0f);
    for (int i = 0; i < spottedDifferences.size(); ++i)
    {
        glColor3f(0.7, 0.1, 1.0);
        drawHollowCircle(spottedDifferences[i].first, spottedDifferences[i].second, 0.065);
    }

    glFlush();
}

//---------------------------
///    display Function
//---------------------------
void Level3()
{
    keyMouse1 = 8;

    background2();
    //text "Level 3"
    char text1[] = "Lev.3   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
    //question text
    char text2[] = "Find the 8 different spots !";
    glColor3f(1.0, 0.5, 0.6);
    glRasterPos2f(-0.40, 0.65);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Different Drawing
    glPushMatrix();
    glTranslatef(0.5f, -0.5f, 0.0f);
    MainDrawing();
    diffrences();
    glPopMatrix();
    // Main Drawing 
    glPushMatrix();
    glTranslatef(-0.5f, -0.5f, 0.0f);
    MainDrawing();
    windows();
    Bushes();
    //-additional different tree-
    TreeDiff();
    glPopMatrix();
    // Outer Frame Cover -
    outer_frame();
    //text
    char text3[] = "Press On Figure B.";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.2, -0.6);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    // Circle the spotted differences 
    diffrenceCircles();
}

// ---------------------------------------------------------------[ Level 4 ]---------------------------------------------------------------
// Move the stick to solve the equation game (Stick Game) - Suzan Emam

void drawFilledCircle1(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle
    GLfloat twicePi = 1.0f * PI;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (0.04 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

//Background level 4
void BackgroundLevel4()
{
    background2();
    //text "Level 4"
    char text1[] = "Lev.4   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
}

// MatchSticks Object
void MatchSticksObj1()
{
    glColor3f(0.9f, 0.0f, 0.0f);
    drawFilledCircle1(0.0, 0.128, 0.009);

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.6f, 0.2f);
    glVertex2f(-0.008, -0.092);
    glVertex2f(0.008, -0.092);
    glVertex2f(0.008, 0.128);
    glVertex2f(-0.008, 0.128);
    glEnd();
}

// Matchstick Shadow Object
void MatchSticksObj2()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle1(0.0, 0.128, 0.009);

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.008, -0.092);
    glVertex2f(0.008, -0.092);
    glVertex2f(0.008, 0.128);
    glVertex2f(-0.008, 0.128);
    glEnd();
}

// The Equation Consisting of Matchsticks
void Equation()
{
    //Background
    BackgroundLevel4();
    //Message for User
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos3f(-0.85, 0.59, 0.0);
    char message1[] = "Move two matchsticks to make the equation correct";
    for (int i = 0; i < strlen(message1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[i]);

    char text3[] = "1. Choose only two matchsticks from the matchsticks numbered (1-4)";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.8, 0.45);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    char text4[] = "that you want to move. [Use the keyboard - from number 1 to 4]";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.74, 0.38);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text4[i]);
    }

    //4
    glPushMatrix();
    glTranslatef(-0.913, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.655, 0.037, 0.0);
    char stick4[] = "(4)";
    for (int i = 0; i < strlen(stick4); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick4[i]);

    glPushMatrix();
    glTranslatef(-0.676, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.676, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // *
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.090, 0.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.034, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 9
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.405, 0.037, 0.0);
    char stick3[] = "(3)";
    for (int i = 0; i < strlen(stick3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick3[i]);

    glPushMatrix();
    glTranslatef(-0.318, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.081, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.165, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, 0.22, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.082, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, -0.345, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // =
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.040, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.1, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 4
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.262, 0.037, 0.0);
    char stick2[] = "(2)";
    for (int i = 0; i < strlen(stick2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick2[i]);

    glPushMatrix();
    glTranslatef(0.355, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.591, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.507, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.592, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // 6
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, 0.218, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, 0.115, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.762, -0.063, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.70, -0.190, 0.0);
    char stick1[] = "(1)";
    for (int i = 0; i < strlen(stick1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick1[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.917, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, -0.350, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();
}

void DisplayEquation() //KeyboardMove=1
{
    keyMouse1 = 9;
    page = 1;
    Equation();
}

// The Equation if the User Choose Matchstick Number (1)
void EquationOut1()
{
    //Background
    BackgroundLevel4();
    //Message for User
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos3f(-0.85, 0.59, 0.0);
    char message1[] = "Move two matchsticks to make the equation correct";
    for (int i = 0; i < strlen(message1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[i]);

    char text3[] = "1. Choose only two matchsticks from the matchsticks numbered (1-4)";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.8, 0.45);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    char text4[] = "that you want to move. [Use the keyboard - from number 1 to 4]";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.74, 0.38);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text4[i]);
    }

    //4
    glPushMatrix();
    glTranslatef(-0.913, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.655, 0.037, 0.0);
    char stick4[] = "(4)";
    for (int i = 0; i < strlen(stick4); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick4[i]);

    glPushMatrix();
    glTranslatef(-0.676, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.676, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // *
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.090, 0.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.034, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 9
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.405, 0.037, 0.0);
    char stick3[] = "(3)";
    for (int i = 0; i < strlen(stick3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick3[i]);

    glPushMatrix();
    glTranslatef(-0.318, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.081, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.165, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, 0.22, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.082, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, -0.345, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // =
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.040, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.1, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 4
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.262, 0.037, 0.0);
    char stick2[] = "(2)";
    for (int i = 0; i < strlen(stick2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick2[i]);

    glPushMatrix();
    glTranslatef(0.355, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.591, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.507, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.592, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // 6
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, 0.218, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, 0.115, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.762, -0.063, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.917, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, -0.350, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();
}

// The Equation if the User Choose Matchstick Number (4)
void DisplayEquationOut1() //KeyboardMove=2
{
    keyMouse1 = 9;
    page = 2;
    EquationOut1();
}

void EquationOut4()
{
    //Background
    BackgroundLevel4();
    //Message for User
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos3f(-0.85, 0.59, 0.0);
    char message1[] = "Move two matchsticks to make the equation correct";
    for (int i = 0; i < strlen(message1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[i]);

    char text3[] = "1. Choose only two matchsticks from the matchsticks numbered (1-4)";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.8, 0.45);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    char text4[] = "that you want to move. [Use the keyboard - from number 1 to 4]";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.74, 0.38);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text4[i]);
    }

    //4
    glPushMatrix();
    glTranslatef(-0.913, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.676, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // *
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.090, 0.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.034, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 9
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.405, 0.037, 0.0);
    char stick3[] = "(3)";
    for (int i = 0; i < strlen(stick3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick3[i]);

    glPushMatrix();
    glTranslatef(-0.318, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.081, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.165, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, 0.22, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.082, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, -0.345, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // =
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.040, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.1, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 4
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.262, 0.037, 0.0);
    char stick2[] = "(2)";
    for (int i = 0; i < strlen(stick2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick2[i]);

    glPushMatrix();
    glTranslatef(0.355, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.591, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.507, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.592, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // 6
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, 0.218, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, 0.115, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.762, -0.063, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.70, -0.190, 0.0);
    char stick1[] = "(1)";
    for (int i = 0; i < strlen(stick1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick1[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.917, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, -0.350, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();
}

void DisplayEquationOut4() //KeyboardMove=3
{
    keyMouse1 = 9;
    page = 3;
    EquationOut4();
}


// The Equation with Shadows Answers
void ShadowsAnswers()
{
    //Background
    BackgroundLevel4();
    //Message for User
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos3f(-0.85, 0.6, 0.0);
    char message1[] = "Move two matchsticks to make the equation correct";
    for (int i = 0; i < strlen(message1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[i]);

    char text3[] = "2. Choose two shades to place your chosen matchsticks.";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.66, 0.48);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    char text4[] = "[Use the keyboard - from number 1 to 5]";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.48, 0.4);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text4[i]);
    }

    //4
    glPushMatrix();
    glTranslatef(-0.913, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.676, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // *
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.090, 0.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.034, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 9
    glPushMatrix();
    glTranslatef(-0.318, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.081, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.165, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, 0.22, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.082, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, -0.345, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // =
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.040, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.1, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 4
    glPushMatrix();
    glTranslatef(0.355, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.591, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.507, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.592, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // 6
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, 0.218, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, 0.115, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.762, -0.063, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.917, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, -0.350, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // Shadows Answers
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.83, -0.310, 0.0);
    char Shadow1[] = "(1)";
    for (int i = 0; i < strlen(Shadow1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow1[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.345, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.44, 0.25, 0.0);
    char Shadow2[] = "(2)";
    for (int i = 0; i < strlen(Shadow2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow2[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.510, 0.22, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.44, -0.310, 0.0);
    char Shadow3[] = "(3)";
    for (int i = 0; i < strlen(Shadow3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow3[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.510, -0.345, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.83, 0.25, 0.0);
    char Shadow4[] = "(4)";
    for (int i = 0; i < strlen(Shadow4); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow4[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.758, 0.22, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.407, -0.22, 0.0);
    char Shadow5[] = "(5)";
    for (int i = 0; i < strlen(Shadow5); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow5[i]);

    glPushMatrix();
    glTranslatef(-0.318, -0.24, 0.0);
    MatchSticksObj2();
    glPopMatrix();
}

void DisplayShadowsAnswers() //KeyboardMove=4
{
    keyMouse1 = 9;
    page = 4;
    ShadowsAnswers();
}

// The Equation if the User Choose the Shadow Answer Number (1)
void ShadowsAnswersOut1()
{
    //Background
    BackgroundLevel4();
    //Message for User
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos3f(-0.85, 0.6, 0.0);
    char message1[] = "Move two matchsticks to make the equation correct";
    for (int i = 0; i < strlen(message1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[i]);

    char text3[] = "2. Choose two shades to place your chosen matchsticks.";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.66, 0.48);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    char text4[] = "[Use the keyboard - from number 1 to 5]";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.48, 0.4);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text4[i]);
    }

    //4
    glPushMatrix();
    glTranslatef(-0.913, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.676, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // *
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.090, 0.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.034, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 9
    glPushMatrix();
    glTranslatef(-0.318, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.081, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.165, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, 0.22, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.082, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, -0.345, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // =
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.040, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.1, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 4
    glPushMatrix();
    glTranslatef(0.355, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.591, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.507, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.592, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // 6
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, 0.218, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, 0.115, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.762, -0.063, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.917, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, -0.350, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // Shadows Answers
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.345, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.44, 0.25, 0.0);
    char Shadow2[] = "(2)";
    for (int i = 0; i < strlen(Shadow2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow2[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.510, 0.22, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.44, -0.310, 0.0);
    char Shadow3[] = "(3)";
    for (int i = 0; i < strlen(Shadow3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow3[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.510, -0.345, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.83, 0.25, 0.0);
    char Shadow4[] = "(4)";
    for (int i = 0; i < strlen(Shadow4); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow4[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.758, 0.22, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.407, -0.22, 0.0);
    char Shadow5[] = "(5)";
    for (int i = 0; i < strlen(Shadow5); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow5[i]);

    glPushMatrix();
    glTranslatef(-0.318, -0.24, 0.0);
    MatchSticksObj2();
    glPopMatrix();
}

void DisplayShadowsAnswersOut1() //KeyboardMove=5
{
    keyMouse1 = 9;
    page = 5;
    ShadowsAnswersOut1();
}

// The Equation if the User Choose the Shadow Answer Number (4)
void ShadowsAnswersOut4()
{
    //Background
    BackgroundLevel4();
    //Message for User
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos3f(-0.85, 0.6, 0.0);
    char message1[] = "Move two matchsticks to make the equation correct";
    for (int i = 0; i < strlen(message1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[i]);

    char text3[] = "2. Choose two shades to place your chosen matchsticks.";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.66, 0.48);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    char text4[] = "[Use the keyboard - from number 1 to 5]";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.48, 0.4);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text4[i]);
    }

    //4
    glPushMatrix();
    glTranslatef(-0.913, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.676, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // *
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.090, 0.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.034, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 9
    glPushMatrix();
    glTranslatef(-0.318, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.081, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.165, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, 0.22, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.082, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, -0.345, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // =
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.040, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.1, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 4
    glPushMatrix();
    glTranslatef(0.355, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.591, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.507, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.592, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // 6
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, 0.218, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, 0.115, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.762, -0.063, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.917, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, -0.350, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // Shadows Answers
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.83, -0.310, 0.0);
    char Shadow1[] = "(1)";
    for (int i = 0; i < strlen(Shadow1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow1[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.345, 1.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.44, 0.25, 0.0);
    char Shadow2[] = "(2)";
    for (int i = 0; i < strlen(Shadow2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow2[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.510, 0.22, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.44, -0.310, 0.0);
    char Shadow3[] = "(3)";
    for (int i = 0; i < strlen(Shadow3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow3[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.510, -0.345, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj2();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.758, 0.22, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.407, -0.22, 0.0);
    char Shadow5[] = "(5)";
    for (int i = 0; i < strlen(Shadow5); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, Shadow5[i]);

    glPushMatrix();
    glTranslatef(-0.318, -0.24, 0.0);
    MatchSticksObj2();
    glPopMatrix();
}

void DisplayShadowsAnswersOut4() //KeyboardMove=6
{
    keyMouse1 = 9;
    page = 6;
    ShadowsAnswersOut4();
}

// The Equation with Message if the User not Choose Corect
void EquationError()
{
    //Background
    BackgroundLevel4();
    //Message for User
    glColor3f(0.2f, 0.2f, 0.2f);
    glRasterPos3f(-0.85, 0.59, 0.0);
    char message1[] = "Move two matchsticks to make the equation correct";
    for (int i = 0; i < strlen(message1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[i]);

    char text3[] = "1. Choose only two matchsticks from the matchsticks numbered (1-4)";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.8, 0.45);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
    char text4[] = "that you want to move. [Use the keyboard - from number 1 to 4]";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.74, 0.38);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text4[i]);
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.65, -0.65, 0.0);
    char message3[] = "The choice is not correct, choice again";
    for (int i = 0; i < strlen(message3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message3[i]);

    //4
    glPushMatrix();
    glTranslatef(-0.913, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.655, 0.037, 0.0);
    char stick4[] = "(4)";
    for (int i = 0; i < strlen(stick4); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick4[i]);

    glPushMatrix();
    glTranslatef(-0.676, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.760, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.676, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // *
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.090, 0.0);
    glRotatef(40.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.464, -0.034, 0.0);
    glRotatef(145.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 9
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(-0.405, 0.037, 0.0);
    char stick3[] = "(3)";
    for (int i = 0; i < strlen(stick3); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick3[i]);

    glPushMatrix();
    glTranslatef(-0.318, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.081, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.165, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, 0.22, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.082, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-0.235, -0.345, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // =
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.040, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.17, -0.1, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    // 4
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.262, 0.037, 0.0);
    char stick2[] = "(2)";
    for (int i = 0; i < strlen(stick2); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick2[i]);

    glPushMatrix();
    glTranslatef(0.355, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.591, 0.042, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.507, -0.063, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.592, -0.24, 0.0);
    MatchSticksObj1();
    glPopMatrix();

    // 6
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, 0.218, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, 0.115, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.762, -0.063, 0.0);
    glRotatef(270.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos3f(0.70, -0.190, 0.0);
    char stick1[] = "(1)";
    for (int i = 0; i < strlen(stick1); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, stick1[i]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.68, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.917, -0.170, 0.0);
    glRotatef(180.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.835, -0.350, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    glScalef(1.0, 1.0, 1.0);
    MatchSticksObj1();
    glPopMatrix();
}

void DisplayEquationError() //KeyboardMove=7
{
    keyMouse1 = 9;
    page = 7;
    EquationError();
}

// ---------------------------------------------------------------[ Level 5 ]---------------------------------------------------------------
// Tank filling Game - Huda Ziniy

void TankGame()
{
    //drawing background
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.86f, 0.87f);
    glVertex2f(-0.92f, 0.87f);
    glVertex2f(-0.92f, -0.81f);
    glVertex2f(0.86f, -0.81f);
    glEnd();
    //figure frame
    glBegin(GL_LINE_LOOP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.86f, 0.87f);
    glVertex2f(-0.92f, 0.87f);
    glVertex2f(-0.92f, -0.81f);
    glVertex2f(0.86f, -0.81f);
    glEnd();
    //tap
    glBegin(GL_QUADS); //1
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.86f, 0.75f);
    glVertex2f(0.54f, 0.75f);
    glVertex2f(0.54f, 0.72f);
    glVertex2f(0.86f, 0.72f);
    glEnd();
    glBegin(GL_QUADS); //2
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.58f, 0.72f);
    glVertex2f(0.54f, 0.72f);
    glVertex2f(0.54f, 0.69f);
    glVertex2f(0.58f, 0.69f);
    glEnd();
    glBegin(GL_QUADS); //3
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.59f, 0.69f);
    glVertex2f(0.53f, 0.69f);
    glVertex2f(0.53f, 0.68f);
    glVertex2f(0.59f, 0.68f);
    glEnd();
    glBegin(GL_QUADS); //4
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.63f, 0.77f);
    glVertex2f(0.61f, 0.77f);
    glVertex2f(0.59f, 0.75f);
    glVertex2f(0.65f, 0.75f);
    glEnd();
    glBegin(GL_QUADS); //5
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.63f, 0.79f);
    glVertex2f(0.61f, 0.79f);
    glVertex2f(0.61f, 0.77f);
    glVertex2f(0.63f, 0.77f);
    glEnd();
    glBegin(GL_QUADS); //6
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.626f, 0.8f);
    glVertex2f(0.614f, 0.8f);
    glVertex2f(0.614f, 0.79f);
    glVertex2f(0.626f, 0.79f);
    glEnd();
    glBegin(GL_QUADS); //7
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.66f, 0.81f);
    glVertex2f(0.58f, 0.81f);
    glVertex2f(0.58f, 0.8f);
    glVertex2f(0.66f, 0.8f);
    glEnd();
    //drop
    glColor3f(0.0f, 0.0f, 1.0f);
    drawFilledCircle(0.56, 0.63, 0.02);
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.56f, 0.67f);
    glVertex2f(0.58f, 0.64f);
    glVertex2f(0.54f, 0.64f);
    glEnd();
    //water
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.65f, 0.43f);
    glVertex2f(0.45f, 0.43f);
    glVertex2f(0.45f, 0.4f);
    glVertex2f(0.65f, 0.4f);
    glEnd();
    //tank&pipe line 1
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.45f, 0.6f);
    glVertex2f(0.45f, 0.46f);
    glVertex2f(0.35f, 0.46f);
    glVertex2f(0.35f, 0.36f);
    glVertex2f(0.3f, 0.36f);
    glVertex2f(0.3f, 0.5f);
    glEnd();
    //tank&pipe line 2
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.65f, 0.6f);
    glVertex2f(0.65f, 0.4f);
    glVertex2f(0.45f, 0.4f);
    glVertex2f(0.45f, 0.43f);
    glVertex2f(0.38f, 0.43f);
    glVertex2f(0.38f, 0.33f);
    glVertex2f(0.3f, 0.33f);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(0.22f, 0.3f);
    glVertex2f(0.22f, 0.26f);
    glVertex2f(0.45f, 0.26f);
    glVertex2f(0.45f, 0.3f);
    glEnd();
    //tank&pipe line 3
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.1f, 0.5f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.05f, 0.4f);
    glVertex2f(0.05f, 0.47f);
    glVertex2f(-0.05f, 0.47f);
    glVertex2f(-0.05f, 0.55f);
    glEnd();
    //tank&pipe line 4
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.1f, 0.37f);
    glVertex2f(0.02f, 0.37f);
    glVertex2f(0.02f, 0.44f);
    glVertex2f(-0.05f, 0.44f);
    glVertex2f(-0.05f, 0.47f);
    glEnd();
    //tank&pipe line 5
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.1f, 0.37f);
    glVertex2f(0.1f, 0.3f);
    glVertex2f(0.19f, 0.3f);
    glVertex2f(0.19f, 0.26f);
    glVertex2f(-0.14f, 0.26f);
    glVertex2f(-0.14f, 0.35f);
    glVertex2f(-0.05f, 0.35f);
    glVertex2f(-0.05f, 0.44f);
    glEnd();
    //tank&pipe line 6
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.25f, 0.55f);
    glVertex2f(-0.25f, 0.41f);
    glVertex2f(-0.33f, 0.41f);
    glVertex2f(-0.33f, 0.31f);
    glVertex2f(-0.45f, 0.31f);
    glVertex2f(-0.45f, 0.45f);
    glEnd();
    //tank&pipe line 7
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.65f, 0.45f);
    glVertex2f(-0.65f, 0.25f);
    glVertex2f(-0.45f, 0.25f);
    glVertex2f(-0.45f, 0.28f);
    glVertex2f(-0.3f, 0.28f);
    glVertex2f(-0.3f, 0.38f);
    glVertex2f(-0.25f, 0.38f);
    glVertex2f(-0.25f, 0.35f);
    glVertex2f(-0.17f, 0.35f);
    glVertex2f(-0.17f, 0.23f);
    glVertex2f(0.45f, 0.23f);
    glVertex2f(0.45f, 0.16f);
    glVertex2f(0.37f, 0.16f);
    glVertex2f(0.37f, -0.04f);
    glVertex2f(0.3f, -0.04f);
    glVertex2f(0.3f, 0.1f);
    glEnd();
    //tank&pipe line 8
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.65f, 0.35f);
    glVertex2f(-0.78f, 0.35f);
    glVertex2f(-0.78f, -0.02f);
    glVertex2f(-0.7f, -0.02f);
    glVertex2f(-0.7f, 0.05f);
    glEnd();
    //tank&pipe line 9
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.65f, 0.3f);
    glVertex2f(0.65f, 0.1f);
    glVertex2f(0.45f, 0.1f);
    glVertex2f(0.45f, 0.13f);
    glVertex2f(0.4f, 0.13f);
    glVertex2f(0.4f, -0.15f);
    glVertex2f(0.45f, -0.15f);
    glEnd();
    //tank&pipe line 10
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.1f, 0.04f);
    glVertex2f(0.06f, 0.04f);
    glVertex2f(0.06f, 0.07f);
    glVertex2f(-0.1f, 0.07f);
    glVertex2f(-0.1f, 0.2f);
    glEnd();
    //tank&pipe line 11
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.3f, 0.2f);
    glVertex2f(-0.3f, 0.05f);
    glVertex2f(-0.4f, 0.05f);
    glVertex2f(-0.4f, -0.08f);
    glVertex2f(-0.5f, -0.08f);
    glVertex2f(-0.5f, 0.05f);
    glEnd();
    //tank&pipe line 12
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.45f, -0.18f);
    glVertex2f(0.37f, -0.18f);
    glVertex2f(0.37f, -0.07f);
    glVertex2f(0.3f, -0.07f);
    glVertex2f(0.3f, -0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(0.1f, 0.01f);
    glVertex2f(0.03f, 0.01f);
    glVertex2f(0.03f, 0.04f);
    glVertex2f(-0.1f, 0.04f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.3f, 0.02f);
    glVertex2f(-0.37f, 0.02f);
    glVertex2f(-0.37f, -0.11f);
    glVertex2f(-0.5f, -0.11f);
    glVertex2f(-0.5f, -0.15f);
    glVertex2f(-0.7f, -0.15f);
    glVertex2f(-0.7f, -0.05f);
    glVertex2f(-0.78f, -0.05f);
    glVertex2f(-0.78f, -0.44f);
    glVertex2f(-0.7f, -0.44f);
    glVertex2f(-0.7f, -0.3f);
    glEnd();
    //tank&pipe line 13
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.65f, 0.21f);
    glVertex2f(0.75f, 0.21f);
    glVertex2f(0.75f, -0.61f);
    glVertex2f(0.65f, -0.61f);
    glEnd();
    //tank&pipe line 14
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.65f, 0.18f);
    glVertex2f(0.72f, 0.18f);
    glVertex2f(0.72f, -0.24f);
    glVertex2f(0.65f, -0.24f);
    glVertex2f(0.65f, -0.1f);
    glEnd();
    //tank&pipe line 15
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.45f, -0.1f);
    glVertex2f(0.45f, -0.3f);
    glVertex2f(0.53f, -0.3f);
    glVertex2f(0.53f, -0.36f);
    glEnd();
    //tank&pipe line 16
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.57f, -0.36f);
    glVertex2f(0.57f, -0.3f);
    glVertex2f(0.65f, -0.3f);
    glVertex2f(0.65f, -0.27f);
    glVertex2f(0.72f, -0.27f);
    glVertex2f(0.72f, -0.58f);
    glVertex2f(0.65f, -0.58f);
    glEnd();
    //tank&pipe line 17
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.45f, -0.45f);
    glVertex2f(0.45f, -0.47f);
    glVertex2f(0.37f, -0.47f);
    glVertex2f(0.37f, -0.33f);
    glVertex2f(0.2f, -0.33f);
    glVertex2f(0.2f, -0.25f);
    glEnd();
    //tank&pipe line 18
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.0f, -0.25f);
    glVertex2f(0.0f, -0.38f);
    glVertex2f(-0.05f, -0.38f);
    glVertex2f(-0.05f, -0.33f);
    glVertex2f(-0.15f, -0.33f);
    glVertex2f(-0.15f, -0.2f);
    glEnd();
    //tank&pipe line 19
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.35f, -0.2f);
    glVertex2f(-0.35f, -0.23f);
    glVertex2f(-0.45f, -0.23f);
    glVertex2f(-0.45f, -0.32f);
    glVertex2f(-0.5f, -0.32f);
    glVertex2f(-0.5f, -0.3f);
    glEnd();
    //tank&pipe line 20
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.65f, -0.45f);
    glVertex2f(0.65f, -0.65f);
    glVertex2f(0.45f, -0.65f);
    glVertex2f(0.45f, -0.5f);
    glVertex2f(0.34f, -0.5f);
    glVertex2f(0.34f, -0.36f);
    glVertex2f(0.2f, -0.36f);
    glVertex2f(0.2f, -0.45f);
    glVertex2f(0.0f, -0.45f);
    glVertex2f(0.0f, -0.41f);
    glVertex2f(-0.08f, -0.41f);
    glVertex2f(-0.08f, -0.36f);
    glVertex2f(-0.15f, -0.36f);
    glVertex2f(-0.15f, -0.4f);
    glVertex2f(-0.35f, -0.4f);
    glVertex2f(-0.35f, -0.26f);
    glVertex2f(-0.42f, -0.26f);
    glVertex2f(-0.42f, -0.35f);
    glVertex2f(-0.5f, -0.35f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.58f, -0.5f);
    glVertex2f(-0.58f, -0.58f);
    glVertex2f(-0.27f, -0.58f);
    glVertex2f(-0.27f, -0.4f);
    glEnd();
    //tank&pipe line 21
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.53f, -0.65f);
    glVertex2f(0.53f, -0.72f);
    glVertex2f(0.33f, -0.72f);
    glVertex2f(0.33f, -0.58f);
    glVertex2f(0.12f, -0.58f);
    glVertex2f(0.12f, -0.45f);
    glEnd();
    //tank&pipe line 22
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(0.09f, -0.45f);
    glVertex2f(0.09f, -0.58f);
    glVertex2f(-0.24f, -0.58f);
    glVertex2f(-0.24f, -0.4f);
    glEnd();
    //tank&pipe line 23
    glBegin(GL_LINE_STRIP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.65f, 0.38f);
    glVertex2f(-0.81f, 0.38f);
    glVertex2f(-0.81f, -0.47f);
    glVertex2f(-0.7f, -0.47f);
    glVertex2f(-0.7f, -0.5f);
    glVertex2f(-0.61f, -0.5f);
    glVertex2f(-0.61f, -0.61f);
    glVertex2f(0.3f, -0.61f);
    glVertex2f(0.3f, -0.75f);
    glVertex2f(0.56f, -0.75f);
    glVertex2f(0.56f, -0.65f);
    glEnd();
    //number
    char line1[] = "1";
    char line2[] = "2";
    char line3[] = "3";
    char line4[] = "4";
    char line5[] = "5";
    char line6[] = "6";
    char line7[] = "7";
    char line8[] = "8";
    char line9[] = "9";
    char line10[] = "10";
    char line11[] = "11";
    char line12[] = "12";
    char line13[] = "13";
    //number text
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.53, 0.48);
    for (GLint i = 0; i <= strlen(line1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line1[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.18, 0.37);
    for (GLint i = 0; i <= strlen(line2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line2[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.17, 0.42);
    for (GLint i = 0; i <= strlen(line3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line3[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.58, 0.32);
    for (GLint i = 0; i <= strlen(line4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line4[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.62, -0.08);
    for (GLint i = 0; i <= strlen(line5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line5[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.22, 0.07);
    for (GLint i = 0; i <= strlen(line6); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line6[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.18, -0.03);
    for (GLint i = 0; i <= strlen(line7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line7[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.53, 0.17);
    for (GLint i = 0; i <= strlen(line8); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line8[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.53, -0.23);
    for (GLint i = 0; i <= strlen(line9); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line9[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.5, -0.58);
    for (GLint i = 0; i <= strlen(line10); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line10[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(0.055, -0.38);
    for (GLint i = 0; i <= strlen(line11); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line11[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.2999, -0.33);
    for (GLint i = 0; i <= strlen(line12); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line12[i]);
    }
    glColor3f(0.4f, 0.4f, 0.4f);
    glRasterPos2f(-0.65, -0.43);
    for (GLint i = 0; i <= strlen(line13); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line13[i]);
    }
}


void Level5()
{
    keyMouse1 = 10;

    background2();
    //text "Level 5"
    char text1[] = "Lev.5   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
    //question text
    char text2[] = "Which tank will fill up first ?";
    glColor3f(0.7, 0.0, 0.2);
    glRasterPos2f(-0.43, 0.63);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
    }

    glPushMatrix();
    glTranslatef(0.03, -0.13, 0.0);
    glScalef(0.8, 0.8, 1.0);
    TankGame();
    glPopMatrix();

    //text
    char text3[] = "Press The Tank Number.";
    glColor3f(0.0, 0.6, 0.8);
    glRasterPos2f(-0.25, -0.86);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text3[i]);
    }
}

// ---------------------------------------------------------------[ Level 6 ]---------------------------------------------------------------
// Black and white points Game - Haneen Almalki

void Square() { //square one [ques-mid]
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.3f, 0.3f);
    glVertex2f(-0.5f, 0.3f);
    glEnd();
}

void Square2() { //square tow [ques-left]
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.9f, 0.0f);
    glVertex2f(-0.7f, 0.0f);
    glVertex2f(-0.7f, 0.3f);
    glVertex2f(-0.9f, 0.3f);
    glEnd();
}

void Square3() { //square three [ques-right]
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.1f, 0.3f);
    glVertex2f(-0.1f, 0.3f);
    glEnd();
}

void Square4() { //square four [ans-left]
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(0.6f, 0.0f);
    glVertex2f(0.6f, -0.3f);
    glVertex2f(0.4f, -0.3f);
    glEnd();
}

void Square5() { //squara five [ans-right]
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.7f, 0.0f);
    glVertex2f(0.9f, 0.0f);
    glVertex2f(0.9f, -0.3f);
    glVertex2f(0.7f, -0.3f);
    glEnd();
}

void MyLine() { //Draw the boundaries of the second square
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.3f, 0.0f);
    glVertex2f(-0.3f, 0.3f);
    glVertex2f(-0.5f, 0.3f);
    glEnd();
}

void MyLine2() { //Draw the boundaries of the first square
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(-0.9f, 0.0f);
    glVertex2f(-0.7f, 0.0f);
    glVertex2f(-0.7f, 0.3f);
    glVertex2f(-0.9f, 0.3f);
    glEnd();
}

void MyLine3() { //Draw the boundaries of the third square
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.1f, 0.3f);
    glVertex2f(-0.1f, 0.3f);
    glEnd();
}

void MyLine4() { //Draw the boundaries of the fourth square
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(0.6f, 0.0f);
    glVertex2f(0.6f, -0.3f);
    glVertex2f(0.4f, -0.3f);
    glEnd();
}

void MyLine5() { //Draw the boundaries of the five square
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(0.7f, 0.0f);
    glVertex2f(0.9f, 0.0f);
    glVertex2f(0.9f, -0.3f);
    glVertex2f(0.7f, -0.3f);
    glEnd();
}

void line() {

    //Draw the line between the question and the answer
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(0.2f, 0.8f);
    glVertex2f(0.2f, -0.51f);

    //Draw all excess
    glVertex2f(-0.6f, 0.7f);
    glVertex2f(-0.6f, 0.6f);
    glVertex2f(-0.55, 0.65);
    glVertex2f(-0.65, 0.65);

    glVertex2f(-0.6, 0.20);
    glVertex2f(-0.6, 0.10);
    glVertex2f(-0.65, 0.15);
    glVertex2f(-0.55, 0.15);

    glVertex2f(-0.55, -0.35);
    glVertex2f(-0.65, -0.35);
    glVertex2f(-0.60, -0.40);
    glVertex2f(-0.60, -0.30);

    //Draw all equals
    glVertex2f(-0.15, 0.70);
    glVertex2f(-0.25, 0.70);
    glVertex2f(-0.15, 0.65);
    glVertex2f(-0.25, 0.65);

    glVertex2f(-0.15, 0.20);
    glVertex2f(-0.25, 0.20);
    glVertex2f(-0.15, 0.15);
    glVertex2f(-0.25, 0.15);

    glVertex2f(-0.15, -0.40);
    glVertex2f(-0.25, -0.40);
    glVertex2f(-0.15, -0.35);
    glVertex2f(-0.25, -0.35);
    glEnd();
}

void ObjQusetion()
{
    //Call all squares and lines
    glColor3f(0.25f, 0.25f, 0.25f);
    glLineWidth(1.5f);
    line();
    Square();
    Square2();
    Square3();
    MyLine();
    MyLine2();
    MyLine3();
    //

    glPushMatrix(); //The second column
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, -0.50, 0.0);
    MyLine();
    Square();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(-0.0, 0.0, 0.0);
    Square();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.50, 0.0);
    MyLine();
    Square();
    glPopMatrix();
    //

    glPushMatrix(); //The First column 
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, -0.50, 0.0);
    MyLine2();
    Square2();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.0, 0.0);
    Square2();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.50, 0.0);
    MyLine2();
    Square2();
    glPopMatrix();
    //

    glPushMatrix(); //The third column
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, -0.50, 0.0);
    MyLine3();
    Square3();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.0, 0.0);
    Square3();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.50, 0.0);
    MyLine3();
    Square3();
    glPopMatrix();
    //

    //Circles inside the one square
    glColor3f(0.25f, 0.25f, 0.25f);
    drawFilledCircle(-0.86, 0.65, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(-0.77, 0.56, .03);
    drawHollowCircle(-0.86, 0.56, .03);
    drawHollowCircle(-0.77, 0.65, .03);
    drawHollowCircle(-0.8, 0.75, .03);

    //Circles inside the two square
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(-0.75, 0.1, .03);
    drawHollowCircle(-0.75, 0.20, .03);
    drawHollowCircle(-0.80, 0.15, .03);
    drawHollowCircle(-0.85, 0.25, .03);

    //Circles inside the four square
    drawFilledCircle(-0.40, 0.73, .03);
    drawFilledCircle(-0.44, 0.65, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(-0.36, 0.65, .03);
    drawHollowCircle(-0.40, 0.56, .03);

    //Circles inside the five square
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(-0.44, 0.25, .03);
    drawHollowCircle(-0.36, 0.25, .03);
    drawHollowCircle(-0.36, 0.15, .03);
    drawHollowCircle(-0.44, 0.15, .03);
    drawHollowCircle(-0.4, 0.05, .03);

    //Circles inside the six square
    drawFilledCircle(-0.44, -0.25, .03);
    drawFilledCircle(-0.36, -0.25, .03);
    drawFilledCircle(-0.36, -0.35, .03);
    drawFilledCircle(-0.44, -0.35, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(-0.36, -0.45, .03);
    drawHollowCircle(-0.44, -0.45, .03);

    //Circles inside the Seven square
    drawFilledCircle(-0.01, 0.75, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(-0.01, 0.65, .03);
    drawHollowCircle(-0.03, 0.56, .03);

    //Circles inside the eight square
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(-0.01, 0.15, .03);

    //Circles inside the nine square
    drawFilledCircle(-0.01, -0.4, .03);
    drawFilledCircle(-0.02, -0.3, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(0.05, -0.3, .03);

    char line1[] = "?";
    //text
    glColor3f(0.25f, 0.25f, 0.25f);
    glRasterPos2f(-0.81, -0.38);
    for (GLint i = 0; i <= strlen(line1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line1[i]);
    }
}

void ObjAnswer()
{
    //Call all squares and lines
    Square4();
    Square5();
    MyLine4();
    MyLine5();

    glPushMatrix(); // The Fourth column
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.15, -0.47, 0.0);
    MyLine4();
    Square4();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.0, 0.0);
    Square4();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.50, 0.0);
    MyLine4();
    Square4();
    glPopMatrix();
    //

    glPushMatrix(); //The Five column
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.0, 0.0);
    MyLine5();
    Square5();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0, 0.50, 0.0);
    MyLine5();
    Square5();
    glPopMatrix();
    //

    //Circles inside the ten square
    glColor3f(0.25f, 0.25f, 0.25f);
    drawFilledCircle(0.45, 0.44, .03);
    drawFilledCircle(0.55, 0.44, .03);
    drawFilledCircle(0.55, 0.35, .03);
    drawFilledCircle(0.45, 0.35, .03);
    drawFilledCircle(0.45, 0.25, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(0.55, 0.25, .03);

    //Circles inside the thirteen square
    drawFilledCircle(0.75, -0.26, .03);
    drawFilledCircle(0.75, -0.18, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(0.75, -0.10, .03);
    drawHollowCircle(0.84, -0.26, .03);
    drawHollowCircle(0.84, -0.18, .03);
    drawHollowCircle(0.84, -0.10, .03);

    //Circles inside the eleventh square
    drawFilledCircle(0.75, 0.44, .03);
    drawFilledCircle(0.75, 0.35, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(0.85, 0.35, .03);
    drawHollowCircle(0.85, 0.25, .03);

    //Circles inside the twelfth square
    drawFilledCircle(0.45, -0.05, .03);
    drawFilledCircle(0.55, -0.05, .03);
    drawFilledCircle(0.45, -0.15, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(0.55, -0.15, .03);
    drawHollowCircle(0.55, -0.25, .03);
    drawHollowCircle(0.45, -0.25, .03);

    //Circles inside the Fourteen square
    drawFilledCircle(0.6, -0.56, .03);
    drawFilledCircle(0.65, -0.64, .03);
    glLineWidth(0.0f);
    glColor3f(0.25f, 0.25f, 0.25f);
    drawHollowCircle(0.6, -0.69, .03);
    drawHollowCircle(0.7, -0.56, .03);
    drawHollowCircle(0.7, -0.69, .03);

    char line3[] = "A";
    char line4[] = "B";
    char line5[] = "C";
    char line6[] = "D";
    char line7[] = "E";
    //text
    glColor3f(0.25f, 0.25f, 0.25f);
    glRasterPos2f(0.48, 0.11);
    for (GLint i = 0; i <= strlen(line3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line3[i]);
    }
    glColor3f(0.25f, 0.25f, 0.25f);
    glRasterPos2f(0.78, 0.11);
    for (GLint i = 0; i <= strlen(line4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line4[i]);
    }
    glColor3f(0.25f, 0.25f, 0.25f);
    glRasterPos2f(0.48, -0.39);
    for (GLint i = 0; i <= strlen(line5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line5[i]);
    }
    glColor3f(0.25f, 0.25f, 0.25f);
    glRasterPos2f(0.78, -0.39);
    for (GLint i = 0; i <= strlen(line6); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line6[i]);
    }
    glColor3f(0.25f, 0.25f, 0.25f);
    glRasterPos2f(0.64, -0.85);
    for (GLint i = 0; i <= strlen(line7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, line7[i]);
    }
}

void Level6()
{
    keyMouse1 = 11;

    background2();
    //text "Level 6"
    char text1[] = "Lev.6   |";
    glColor3f(0.45, 0.45, 0.45);
    glRasterPos2f(-0.915, 0.85);
    for (GLint i = 0; i <= strlen(text1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
    }
    //question text
    char text2[] = "Find the correct answer !";
    glColor3f(0.3, 0.6, 0.2);
    glRasterPos2f(-0.35, 0.63);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
    }

    glPushMatrix();
    glTranslatef(0.05, -0.3, 0.0);
    ObjQusetion();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.05, -0.01, 0.0);
    ObjAnswer();
    glPopMatrix();
}

// ---------------------------------------------------------------[ Page (Time's Up) ]---------------------------------------------------------------

void PageTimeUp()
{
    keyMouse1 = 12;

    background1();
    background3();
    //text "Back"
    char text7[] = "Back To Start Page";
    glColor3f(1.45, 1.45, 1.45);
    glRasterPos2f(-0.21, -0.8);
    for (GLint i = 0; i <= strlen(text7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text7[i]);
    }
    //text
    char text2[] = "TIME'S UP !";
    glColor3f(0.8, 0.0, 0.1);
    glRasterPos2f(-0.25, 0.25);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
    }
    char text3[] = "You Have Not Completed All Stages!";
    glColor3f(0.4, 0.4, 0.4);
    glRasterPos2f(-0.72, -0.05);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text3[i]);
    }
}

// ---------------------------------------------------[ Page Done Levels ]---------------------------------------------------

void PageDoneLevels()
{
    keyMouse1 = 13;

    background1();
    background3();
    //text "Back"
    char text7[] = "Back To Start Page";
    glColor3f(1.45, 1.45, 1.45);
    glRasterPos2f(-0.21, -0.8);
    for (GLint i = 0; i <= strlen(text7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text7[i]);
    }
    //text
    char text2[] = "Game Finished !";
    glColor3f(0.8, 0.0, 0.1);
    glRasterPos2f(-0.315, 0.24);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
    }
    char text3[] = "It Was A Difficult Challenge!";
    glColor3f(0.4, 0.4, 0.4);
    glRasterPos2f(-0.55, -0.05);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text3[i]);
    }
}

// ---------------------------------------------------[ Successfully Completed Stages Page ]---------------------------------------------------

void PageSuccessful()
{
    keyMouse1 = 14;

    background1();
    background3();
    //text "Next"
    char text7[] = "Next";
    glColor3f(1.45, 1.45, 1.45);
    glRasterPos2f(-0.08, -0.81);
    for (GLint i = 0; i <= strlen(text7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text7[i]);
    }
    //text
    char text2[] = "CONGRATULATIONS !";
    glColor3f(0.8, 0.0, 0.1);
    glRasterPos2f(-0.511, 0.24);
    for (GLint i = 0; i <= strlen(text2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text2[i]);
    }
    char text3[] = "You Have Completed All Stages!";
    glColor3f(0.4, 0.4, 0.4);
    glRasterPos2f(-0.64, -0.05);
    for (GLint i = 0; i <= strlen(text3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text3[i]);
    }
    char text4[] = "Your IQ Is 100%";
    glColor3f(0.8, 0.6, 0.4);
    glRasterPos2f(-0.319, -0.23);
    for (GLint i = 0; i <= strlen(text4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
    }
}

// ---------------------------------------------------------------[ Prize Page ]---------------------------------------------------------------

//function Source: http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
GLuint LoadTexture(const char* filename, int width, int height)
{
    GLuint texture;
    unsigned char* data;
    FILE* file;

    //The following code will read in our RAW file
    fopen_s(&file, image1Path, "rb");

    if (file == NULL)
    {
        cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
        exit(0);
        return 0;
    }

    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);

    // reorder the image colors to RGB not BGR
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;
    }

    // load another texture image
    glGenTextures(1, &texture);            //generate the texture with the loaded data
    glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free(data); //free the texture array
    if (glGetError() != GL_NO_ERROR)
        printf("GLError in genTexture()\n");

    return texture; //return whether it was successfull
}

void PagePrize()
{
    keyMouse1 = 15;

    background1();
    char text11[] = "GET YOUR PRIZE !!";
    glColor3f(0, 0, 0);
    glRasterPos2f(-0.42, 0.6);
    for (GLint i = 0; i <= strlen(text11); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text11[i]);
    }

    //the image (Texture)
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, myTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.6, -0.6, 0);
    glTexCoord2f(1.140, 0.0); glVertex3f(0.6, -0.6, 0);
    glTexCoord2f(1.140, 1.); glVertex3f(0.6, 0.47, 0);
    glTexCoord2f(0.0, 1.); glVertex3f(-0.6, 0.47, 0);
    glEnd();
    glDisable(GL_TEXTURE_2D);

    //button box
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.7f, 0.7f);
    glVertex2f(0.35f, -0.65f);
    glVertex2f(-0.35f, -0.65f);
    glVertex2f(-0.35f, -0.77f);
    glVertex2f(0.35f, -0.77f);
    glEnd();
    //text "Back"
    char text7[] = "Back To Start Page";
    glColor3f(1., 1., 1.);
    glRasterPos2f(-0.321, -0.735);
    for (GLint i = 0; i <= strlen(text7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text7[i]);
    }
}




// ---------------------------------------------------------------[ Transition Function ]---------------------------------------------------------------

static void special(int key, int x, int y)
{
    //handle special keys
    switch (key) {
    case GLUT_KEY_HOME:
        break;
    case GLUT_KEY_LEFT:
        break;
    case GLUT_KEY_RIGHT:
        break;
    case GLUT_KEY_UP:
        break;
    case GLUT_KEY_DOWN:
        break;
    default:
        break;
    }
}

// ---------------------------------------------------------------[ Mouse ]
static void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            // --------------> page 2 - game definition
            if (keyMouse1 == 1) {
                if (x >= 199 && x <= 299 && y >= 413 && y <= 438 && counter == 0) {
                    next1 = 2;
                }
            }
            // --------------> page 3 - game rules
            if (keyMouse1 == 2) {
                if (x >= 204 && x <= 295 && y >= 434 && y <= 455 && counter == 0) {
                    next1 = 3;
                }
            }
            // --------------> page 4 - start window
            if (keyMouse1 == 3) {
                if (x >= 227 && x <= 274 && y >= 204 && y <= 250) {
                    next1 = 4;
                    startGame = 1;
                    moveLevel = 1;
                    timeControl = 0;
                }
            }
            // --------------> level 1
            if (keyMouse1 == 4) {
                //correct answer
                if (x >= 311 && x <= 350 && y >= 327 && y <= 363 && moveLevel == 1) {
                    flag = 1;
                    IQ = IQ + 5;
                    CountmoveLevel = CountmoveLevel + 1;
                    next1 = 5;
                    moveLevel = 2;
                    skip = 2;
                    L1 == true;
                }
                //skip level 1
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && skip == 1) {
                    CountSkip = CountSkip + 1;
                    next1 = 5;
                    moveLevel = 2;
                    skip = 2;
                }
            }
            // --------------> level 2
            if (keyMouse1 == 5) { // game 1
                //correct answer 
                if (x >= 223 && x <= 277 && y >= 400 && y <= 451 && moveLevel == 2 && level2Games == 1) {
                    IQ = IQ + 3;
                    level2Games = 2;
                    skipLevel2 = 2;
                }
                //skip level 2 - game 1
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && moveLevel == 2 && skipLevel2 == 1) {
                    level2Games = 2;
                    skipLevel2 = 2;
                }
            }
            if (keyMouse1 == 6) { // game 2
                //correct answer 
                if (x >= 223 && x <= 277 && y >= 135 && y <= 187 && moveLevel == 2 && level2Games == 2) {
                    IQ = IQ + 3;
                    level2Games = 3;
                    skipLevel2 = 3;
                }
                //skip level 2 - game 2
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && moveLevel == 2 && skipLevel2 == 2) {
                    level2Games = 3;
                    skipLevel2 = 3;
                }
            }
            if (keyMouse1 == 7) { // game 3
                //correct answer 
                if (x >= 223 && x <= 277 && y >= 135 && y <= 187 && moveLevel == 2 && level2Games == 3) {
                    IQ = IQ + 3;
                    CountmoveLevel = CountmoveLevel + 1;
                    level2Games = 4;
                    skipLevel2 = 4;
                    next1 = 6;
                    moveLevel = 3;
                    skip = 3;
                    L2 == true;
                }
                //skip level 2 - game 3
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && moveLevel == 2 && skipLevel2 == 3) {
                    CountSkip = CountSkip + 1;
                    level2Games = 4;
                    skipLevel2 = 4;
                    next1 = 6;
                    moveLevel = 3;
                    skip = 3;
                }
            }
            // --------------> level 3
            if (keyMouse1 == 8) {
                //skip level 3
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && skip == 3) {
                    CountSkip = CountSkip + 1;
                    next1 = 7;
                    moveLevel = 4;
                    skip = 4;
                }
            }
            // --------------> level 4
            if (keyMouse1 == 9) {
                //skip level 4
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && skip == 4) {
                    CountSkip = CountSkip + 1;
                    next1 = 8;
                    moveLevel = 5;
                    skip = 5;
                }
            }
            // --------------> level 5
            if (keyMouse1 == 10) {
                //correct answer
                if (x >= 126 && x <= 150 && y >= 349 && y <= 375 && moveLevel == 5) {
                    IQ = IQ + 25;
                    CountmoveLevel = CountmoveLevel + 1;
                    next1 = 9;
                    moveLevel = 6;
                    skip = 6;
                    L5 == true;
                }
                //skip level 5
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && skip == 5) {
                    CountSkip = CountSkip + 1;
                    next1 = 9;
                    moveLevel = 6;
                    skip = 6;
                }
            }
            // --------------> level 6
            if (keyMouse1 == 11) {
                //correct answer
                if (x >= 377 && x <= 421 && y >= 377 && y <= 439 && moveLevel == 6) {
                    IQ = IQ + 30;
                    CountmoveLevel = CountmoveLevel + 1;
                    next1 = 10;
                    moveLevel = 7;
                    skip = 7;
                    L6 == true;
                    timeControl = 2;
                }
                //skip level 6
                if (x >= 460 && x <= 474 && y >= 25 && y <= 39 && skip == 6) {
                    CountSkip = CountSkip + 1;
                    next1 = 10;
                    moveLevel = 7;
                    skip = 7;
                    timeControl = 2;
                }
            }
            // --------------> Page - Time's Up
            if (keyMouse1 == 12) {
                if (x >= 184 && x <= 314 && y >= 433 && y <= 456 && CountmoveLevel < 6) {
                    startGame = 0;
                    next1 = 3;
                    timeControl = 2;
                    moveLevel = 0;
                    CountmoveLevel = 0;
                    flag = 0;
                    skip = 1;
                    CountSkip = 0;
                    IQ = 0;
                    level2Games = 1;
                    skipLevel2 = 1;
                    transitionToScene2 = false;
                    spottedIndices.clear();
                    spottedDifferences.clear();
                    page = 0;
                    KeyboardMove = 0;
                    L1 = false;
                    L2 = false;
                    L3 = false;
                    L4 = false;
                    L5 = false;
                    L6 = false;
                }
            }
            // --------------> Page Done Levels
            if (keyMouse1 == 13) {
                if (x >= 184 && x <= 314 && y >= 433 && y <= 456 && moveLevel == 7) {
                    startGame = 0;
                    next1 = 3;
                    timeControl = 2;
                    moveLevel = 0;
                    CountmoveLevel = 0;
                    flag = 0;
                    skip = 1;
                    CountSkip = 0;
                    IQ = 0;
                    level2Games = 1;
                    skipLevel2 = 1;
                    transitionToScene2 = false;
                    spottedIndices.clear();
                    spottedDifferences.clear();
                    page = 0;
                    KeyboardMove = 0;
                    L1 = false;
                    L2 = false;
                    L3 = false;
                    L4 = false;
                    L5 = false;
                    L6 = false;
                }
            }
            // --------------> Page Successfully Completed Stages
            if (keyMouse1 == 14) {
                if (x >= 184 && x <= 314 && y >= 433 && y <= 456 && moveLevel == 7) {
                    next1 = 11;
                }
            }
            // --------------> Prize Page
            if (keyMouse1 == 15) {
                if (x >= 166 && x <= 332 && y >= 415 && y <= 438 && moveLevel == 7) {
                    startGame = 0;
                    next1 = 3;
                    timeControl = 2;
                    moveLevel = 0;
                    CountmoveLevel = 0;
                    flag = 0;
                    skip = 1;
                    CountSkip = 0;
                    IQ = 0;
                    level2Games = 1;
                    skipLevel2 = 1;
                    transitionToScene2 = false;
                    spottedIndices.clear();
                    spottedDifferences.clear();
                    page = 0;
                    KeyboardMove = 0;
                    L1 = false;
                    L2 = false;
                    L3 = false;
                    L4 = false;
                    L5 = false;
                    L6 = false;
                }
            }


        }
    }

    // --------------> level 3
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (keyMouse1 == 8) {

            // Convert mouse coordinates to OpenGL viewport coordinates
            float openglX = (static_cast<float>(x) / win_width) * 2 - 1;
            float openglY = 1 - (static_cast<float>(y) / win_hight) * 2;

            if (spottedIndices.size() <= 8 && moveLevel == 3) {
                // Check if the click matches any correct difference
                for (int i = 0; i < correctDifferences.size(); ++i)
                {
                    const auto& difference = correctDifferences[i];
                    if (openglX >= difference.first - 0.05f &&
                        openglX <= difference.first + 0.05f &&
                        openglY >= difference.second - 0.05f &&
                        openglY <= difference.second + 0.05f)
                    {
                        // Check if the difference has already been spotted
                        if (std::find(spottedIndices.begin(), spottedIndices.end(), i) != spottedIndices.end()) {
                            // Difference has already been spotted, no action needed
                            break;
                        }

                        // Correct difference found, add the index to spottedIndices
                        spottedIndices.push_back(i);
                        spottedDifferences.push_back({ openglX, openglY });
                        std::cout << "Correct difference found at (" << openglX << ", " << openglY << ")" << std::endl;
                        break;
                    }
                }
            }
        }
    }

    if (button == GLUT_RIGHT_BUTTON) {
        if (state == GLUT_UP) {

        }
    }
}

static void motion(int x, int y) {}

// ---------------------------------------------------------------[ Keyboard ]
static void key(unsigned char keyPressed, int x, int y) //key handling
{
    if (page == 1)
    {
        if (keyPressed == '1')
        {
            KeyboardMove = 2;
        }
        else if (keyPressed == '4')
        {
            KeyboardMove = 3;
        }
        else
        {
            KeyboardMove = 7;
        }
    }

    if (page == 2)
    {
        if (keyPressed == '4')
        {
            KeyboardMove = 4;
        }
        else
        {
            KeyboardMove = 7;
        }

    }

    if (page == 3)
    {
        if (keyPressed == '1')
        {
            KeyboardMove = 4;
        }
        else
        {
            KeyboardMove = 7;
        }

    }

    if (page == 4)
    {
        if (keyPressed == '1')
        {
            KeyboardMove = 5;
        }
        else if (keyPressed == '4')
        {
            KeyboardMove = 6;
        }
        else
        {
            KeyboardMove = 7;
        }
    }

    if (page == 5)
    {
        if (keyPressed == '4')
        {
            // here game after my game
            IQ = IQ + 20;
            CountmoveLevel = CountmoveLevel + 1;
            next1 = 8;
            moveLevel = 5;
            skip = 5;
            L4 == true;
        }
        else
        {
            KeyboardMove = 7;
        }

    }

    if (page == 6)
    {
        if (keyPressed == '1')
        {
            //here game after my game , must be in too
            IQ = IQ + 20;
            CountmoveLevel = CountmoveLevel + 1;
            next1 = 8;
            moveLevel = 5;
            skip = 5;
            L4 == true;
        }
        else
        {
            KeyboardMove = 7;
        }

    }

    if (page == 7)
    {
        if (keyPressed == '1')
        {
            KeyboardMove = 2;
        }
        else if (keyPressed == '4')
        {
            KeyboardMove = 3;
        }
        else
        {
            KeyboardMove = 7;
        }
    }
}

static void play(void)
{
    glutPostRedisplay();
}

void init() {
    //------- Texture ---------
    myTexture = LoadTexture(image1Path, 680, 680);
    if (myTexture == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture << endl;
    //--------------------------
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void reshapeFunc(GLint new_width, GLint new_hight)
{
    glViewport(0, 0, new_width, new_hight);
    win_width = new_width;
    win_hight = new_hight;
}



// ---------------------------------------------------------------[ Display Function ]---------------------------------------------------------------

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //-------------------[ Page 1 ]
    if (counter <= 10 && next1 == 0) {
        Introduction();
        if (counter == 10) {
            next1 = 1;
            keyMouse1 = 1;
        }
    }
    //-------------------[ Page 2 ]
    if (next1 == 1) {
        Page2();
        timeControl = 2;
    }
    //-------------------[ Page 3 ]
    if (next1 == 2) {
        Page3();
    }
    //-------------------[ Page 4 ]
    if (startGame == 0 && next1 == 3) {
        Page4();
    }
    if (startGame == 1) {
        //-------------------[ Level 1 ]
        if (next1 == 4) {
            if (counter >= 1 && counter <= 590) {
                Level1();
            }
        }
        //-------------------[ Level 2 ]
        if (next1 == 5) {
            if (counter >= 1 && counter <= 590 && level2Games == 1) {
                level2Game1();
            }
        }
        if (next1 == 5) {
            if (counter >= 1 && counter <= 590 && level2Games == 2) {
                level2Game2();
            }
        }
        if (next1 == 5) {
            if (counter >= 1 && counter <= 590 && level2Games == 3) {
                level2Game3();
            }
        }
        //-------------------[ Level 3 ]
        if (next1 == 6) {
            if (counter >= 1 && counter <= 590) {
                //correct answer
                if (moveLevel == 3) {
                    if (!transitionToScene2) {
                        Level3();    //display the first and main scene
                        if (spottedIndices.size() == 8) {
                            IQ = IQ + 11;
                            CountmoveLevel = CountmoveLevel + 1;
                            next1 = 7;
                            moveLevel = 4;
                            skip = 4;
                            transitionToScene2 = true;
                            L3 == true;
                        }
                    }
                }
            }
        }
        //-------------------[ Level 4 ]
        if (next1 == 7) {
            if (counter >= 1 && counter <= 590 && moveLevel == 4) {
                DisplayEquation();
            }
            if (counter >= 1 && counter <= 590 && KeyboardMove == 1) {
                DisplayEquation();
            }
            if (counter >= 1 && counter <= 590 && KeyboardMove == 2) {
                DisplayEquationOut1();
            }
            if (counter >= 1 && counter <= 590 && KeyboardMove == 3) {
                DisplayEquationOut4();
            }
            if (counter >= 1 && counter <= 590 && KeyboardMove == 4) {
                DisplayShadowsAnswers();
            }
            if (counter >= 1 && counter <= 590 && KeyboardMove == 5) {
                DisplayShadowsAnswersOut1();
            }
            if (counter >= 1 && counter <= 590 && KeyboardMove == 6) {
                DisplayShadowsAnswersOut4();
            }
            if (counter >= 1 && counter <= 590 && KeyboardMove == 7) {
                DisplayEquationError();
            }
        }
        //-------------------[ Level 5 ]
        if (next1 == 8) {
            if (counter >= 1 && counter <= 590) {
                Level5();
                page = 0;
            }
        }
        //-------------------[ Level 6 ]
        if (next1 == 9) {
            if (counter >= 1 && counter <= 590) {
                Level6();
            }
        }
        //-------------------[ Page Done Levels ]
        if (next1 == 10) {
            if (CountSkip <= 6 && IQ < 100) {
                if (CountmoveLevel == 0) {
                    PageDoneLevels();
                    char text4[] = "Your IQ Is 0%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 1) {
                    PageDoneLevels();
                    char text4[] = "Your IQ Is 17%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 2) {
                    PageDoneLevels();
                    char text4[] = "Your IQ Is 34%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 3) {
                    PageDoneLevels();
                    char text4[] = "Your IQ Is 51%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 4) {
                    PageDoneLevels();
                    char text4[] = "Your IQ Is 68%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 5) {
                    PageDoneLevels();
                    char text4[] = "Your IQ Is 85%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
            }
        }
        //-------------------[ Page Successfully Completed Stages ]
        if (next1 == 10) {
            if (CountmoveLevel == 6 && IQ == 100) {
                PageSuccessful();
            }
        }
        //-------------------[ Prize Page ]
        if (next1 == 11) {
            if (CountmoveLevel == 6 && IQ == 100) {
                PagePrize();
            }
        }
        //-------------------[ Page - Time's Up ]
        if (counter > 590) {
            if (CountmoveLevel < 6 && IQ < 100) {
                if (CountmoveLevel == 0) {
                    PageTimeUp();
                    char text4[] = "Your IQ Is 0%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 1) {
                    PageTimeUp();
                    char text4[] = "Your IQ Is 17%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 2) {
                    PageTimeUp();
                    char text4[] = "Your IQ Is 34%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 3) {
                    PageTimeUp();
                    char text4[] = "Your IQ Is 51%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 4) {
                    PageTimeUp();
                    char text4[] = "Your IQ Is 68%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
                if (CountmoveLevel == 5) {
                    PageTimeUp();
                    char text4[] = "Your IQ Is 85%";
                    glColor3f(0.8, 0.6, 0.4);
                    glRasterPos2f(-0.3, -0.23);
                    for (GLint i = 0; i <= strlen(text4); i++) {
                        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text4[i]);
                    }
                }
            }
        }

    }
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); // Specify the display Mode ñ RGB, RGBA or color
    glutInitWindowSize(500, 500); // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow("IntelliQube"); // Create a window with the given title
    init();

    glutIdleFunc(play);
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFunc);
    //glutPassiveMotionFunc(mouseTracking); // تتبع احداثيات الفارة
    glutTimerFunc(gap, MyTimer, counter); //timer
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(key);
    glutSpecialFunc(special);

    glutMainLoop(); // Enter the infinitely event-processing loop

    return 0;
}

