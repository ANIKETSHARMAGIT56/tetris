#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <GL/glut.h>
#include <stdbool.h>
#define padding 5.99
#define I8BIT_TO_FLOAT 0.003921569
char colofblocks[20][10] = {0};
bool matrixdata[20][10] = {0};
char locat=0;
// i am using unsigned char becuse i only want to use 8 bit numbers and char only uses 8 bits
unsigned char colors[5][5][3] =
    {{                 // the green box
      {0, 75, 0},      //bottom
      {76, 255, 76},   //left
      {180, 255, 180}, //top
      {0, 179, 0},     //right
      {0, 255, 0}},
     {
         //red box
         {75, 0, 0},      //bottom
         {255, 76, 76},   //left
         {255, 180, 180}, //top
         {179, 0, 0},     //right
         {255, 0, 0}      //center
     },
     {
         //blue
         {0, 0, 75},      //bottom
         {76, 76, 255},   //left
         {180, 180, 255}, //top
         {0, 0, 179},     //right
         {0, 0, 255}      //center
     },
     {
         //orange
         {75, 30, 0},     //bottom
         {255, 161, 76},  //left
         {255, 215, 180}, //top
         {179, 82, 0},    //right
         {255, 120, 0}    //center
     },
     {
         //orange
         {58, 0, 58},     //bottom
         {220, 76, 220},  //left
         {240, 180, 240}, //top
         {143, 0, 143},   //right
         {205, 0, 205}    //center
     }};
void renderbox(float x, float y, int size, int color)
{
    //bottom box
    glBegin(GL_POLYGON);
    glColor3f(I8BIT_TO_FLOAT * colors[color][0][0], I8BIT_TO_FLOAT * colors[color][0][1], I8BIT_TO_FLOAT * colors[color][0][2]);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size - size / padding, y + size / padding);
    glVertex2f(x + size / padding, y + size / padding);
    glEnd();
    //left box
    glBegin(GL_POLYGON);
    glColor3f(I8BIT_TO_FLOAT * colors[color][1][0], I8BIT_TO_FLOAT * colors[color][1][1], I8BIT_TO_FLOAT * colors[color][1][2]);
    glVertex2f(x, y);
    glVertex2f(x, y + size);
    glVertex2f(x + size / padding, y + size - size / padding);
    glVertex2f(x + size / padding, y + size / padding);
    glEnd();
    //top box
    glBegin(GL_POLYGON);
    glColor3f(I8BIT_TO_FLOAT * colors[color][2][0], I8BIT_TO_FLOAT * colors[color][2][1], I8BIT_TO_FLOAT * colors[color][2][2]);
    glVertex2f(x, y + size);
    glVertex2f(x + size, y + size);
    glVertex2f(x + size - size / padding, y + size - size / padding);
    glVertex2f(x + size / padding, y + size - size / padding);
    glEnd();
    //right box
    glBegin(GL_POLYGON);
    glColor3f(I8BIT_TO_FLOAT * colors[color][3][0], I8BIT_TO_FLOAT * colors[color][3][1], I8BIT_TO_FLOAT * colors[color][3][2]);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x + size - size / padding, y + size - size / padding);
    glVertex2f(x + size - size / padding, y + size / padding);
    glEnd();
    //center box
    glBegin(GL_POLYGON);
    glColor3f(I8BIT_TO_FLOAT * colors[color][4][0], I8BIT_TO_FLOAT * colors[color][4][1], I8BIT_TO_FLOAT * colors[color][4][2]);
    glVertex2f(x + size / padding, y + size / padding);
    glVertex2f(x + size / padding, y + size - size / padding);
    glVertex2f(x + size - size / padding, y + size - size / padding);
    glVertex2f(x + size - size / padding, y + size / padding);
    glEnd();
}
void setbox(int x, int y, int color, bool value)
{
    matrixdata[y][x] = value;
    colofblocks[y][x] = color;
}
void setshape(int x, int y, int shape, int orientation, int color, int value)
{
    if (shape == 1)
    {
        if (orientation == 1)
        {
            setbox(x, y, color, value);
            setbox(x + 1, y, color, value);
            setbox(x + 2, y, color, value);
            setbox(x + 1, y + 1, color, value);
        }
        if (orientation == 2)
        {
            setbox(x,y,color,value);
            setbox(x+1,y,color,value);
            setbox(x+2,y+1,color,value);
            setbox(x-1,y+1,color,value);
        }
    }
}
void keyboard(unsigned char key,int x,int y)
{
    if(key=='a'){
        if (!(locat==0))
        {
            locat--;
        }
    }
    if(key=='d'){
        if (!(locat==9)){
            locat++;
        }
    }
}
void refresh(){
for (int i = 0; i < 20; i++)
    {
        
        for (int s = 0; s < 10; s++)
        {
            if (matrixdata[i][s] == 1)
            {
                renderbox(s * 5, i * 5, 5, colofblocks[i][s]);
            }
        }
    }
}
int i=18;
int tempx=0;
int tempy=0;
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (i>0 && matrixdata[i-1][locat]==0){
    setbox(tempx,tempy, 1,0);
        i--;
    setbox(locat, i, 1, 1);
    tempx=locat;
    tempy=i;
    }
    else{
    i=20;
    tempx=0;
    tempy=20;
    }
    refresh();
    glutSwapBuffers();
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 50, 0, 100);
}
void timer(int a)
{
    glutPostRedisplay();
    glutTimerFunc(1000/6, timer, 0);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(250, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
}
