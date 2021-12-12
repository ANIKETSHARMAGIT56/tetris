#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <GL/glut.h>
#include <stdbool.h>
#include "../include/coordinates.h"
#define padding 5.99
#define I8BIT_TO_FLOAT 0.003921569
#define nMax 4
#define nMin 0
#define gametickspeed 7
#define matrix_width 10
#define go_down \
    i--;        \
    iterations = 0;
#define go_right   \
    direction = 0; \
    locat++;
#define go_left    \
    direction = 0; \
    locat--;
#define resetit     \
    col = gennum(); \
    tempx = 0;      \
    tempy = 20;     \
    locat = 5;
char colofblocks[20][matrix_width] = {0};
bool matrixdata[20][matrix_width] = {0};
int iterations = 0;
char locat = 0;
int8_t direction = 0;
bool resetsignal = 1;
bool orichangesignal=0;
int orival=2;
int gennum()
{
    int random = rand() % ((nMax + 1) - nMin) + nMin;
    return random;
}

int max(int al, int bl, int cl, int dl)  
{
    int a=al;
    int b=bl;
    int c=cl;
    int d=dl;
    if (a==255)
    {
        a=0;
    }
    if (b==255)
    {
        b=0;
    }
    if (c==255)
    {
        c=0;
    }    
    if (d==255)
    {
        d=0;
    }
    if (a > b) {  
        if (a > c) {  
            if (a > d) {  
                return a;  
            }  
            else {  
                return d;  
            }  
        }  
    }  
    else if (b > c) {  
        if (b > d) {  
            return b;  
        }  
        else {
            return d;  
        }  
    }  
    else if (c > d) {  
        return c;  
    }  
    else {
        return d;  
    }
}
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
bool matval(int x, int y)
{
    if (x > 255 && y > 255)
    {
        return 0;
    }
    else
    {
        return matrixdata[y][x];
    }
}
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
void keyboard(unsigned char key, int x, int y)
{
    if (key == 'a' | key == 'A')
    {
        direction = -1;
    }
    if (key == 'd' | key == 'D')
    {
        direction = 1;
    }
    if (key == 'w' | key == 'W')
    {
        orichangesignal=1;
    }
}
void refresh()
{
    for (int i = 0; i < 20; i++)
    {

        for (int s = 0; s < matrix_width; s++)
        {
            if (matrixdata[i][s] == 1)
            {
                renderbox(s * 5, i * 5, 5, colofblocks[i][s]);
            }
        }
    }
}
int i = 18;
int tempx = 0;
int tempy = 0;
int col = 0;
int colldownfunc(int shape ,int orientation ,int box ,int xy)
{
    for (int i = 0; i < 4; i++)
    {
        if (shapes[shape-1][orientation-1][box][0]==shapes[shape-1][orientation-1][i][0])
        {
            if(shapes[shape-1][orientation-1][box][1]-1==shapes[shape-1][orientation-1][i][1])
            {
                return 255;
            }
            else
            {
                if (xy==0)
                {
                    return shapes[shape-1][orientation-1][box][0];
                }
                if (xy==1)
                {
                    return shapes[shape-1][orientation-1][box][1]-1;
                }
            }
        }
    }
}
void displayshape(int shape)
{
    if (resetsignal == 1)
    {
        i = 17;
        resetsignal = 0;
    }
    if (i > 0 
    && matval(locat + colldown[shape - 1][orival - 1][0][0], i + colldown[shape - 1][orival - 1][0][1]) == 0
    && matval(locat + colldown[shape - 1][orival - 1][1][0], i + colldown[shape - 1][orival - 1][1][1]) == 0
    && matval(locat + colldown[shape - 1][orival - 1][2][0], i + colldown[shape - 1][orival - 1][2][1]) == 0
    && matval(locat + colldown[shape - 1][orival - 1][3][0], i + colldown[shape - 1][orival - 1][3][1]) == 0
    )
    {
        iterations++;
        for (int n = 0; n < 4; n++)
        {
            setbox(tempx + shapes[shape - 1][orival - 1][n][0], tempy + shapes[shape - 1][orival - 1][n][1], col, 0);
            
        }
        
        if (iterations == 10)
        {
            go_down;
        }
        if (direction == 1 
        && !(locat == matrix_width - collright[shape - 1][orival - 1][0][0])
        && !(locat == matrix_width - collright[shape - 1][orival - 1][1][0])
        && !(locat == matrix_width - collright[shape - 1][orival - 1][2][0])
        && !(locat == matrix_width - collright[shape - 1][orival - 1][3][0])
        && matval(locat + collright[shape - 1][orival - 1][0][0], i + collright[shape - 1][orival - 1][0][1]) == 0
        && matval(locat + collright[shape - 1][orival - 1][1][0], i + collright[shape - 1][orival - 1][1][1]) == 0
        && matval(locat + collright[shape - 1][orival - 1][2][0], i + collright[shape - 1][orival - 1][2][1]) == 0
        && matval(locat + collright[shape - 1][orival - 1][3][0], i + collright[shape - 1][orival - 1][3][1]) == 0)
        {
            go_right;
        }
        if (orichangesignal==1)
        {
            int p=orival;
            if (orival==1)
            {
                p=2;
            }
            if (orival==2)
            {
                p=1;
            }
            orival=p;
            orichangesignal=0;
        }
        if (direction == -1 && !(locat == 0)
        && matval(locat + collleft[shape - 1][orival - 1][0][0], i + collleft[shape - 1][orival - 1][0][1]) == 0
        && matval(locat + collleft[shape - 1][orival - 1][1][0], i + collleft[shape - 1][orival - 1][1][1]) == 0
        && matval(locat + collleft[shape - 1][orival - 1][2][0], i + collleft[shape - 1][orival - 1][2][1]) == 0
        && matval(locat + collleft[shape - 1][orival - 1][3][0], i + collleft[shape - 1][orival - 1][3][1]) == 0)
        {
            go_left;
        }
        for (int n = 0; n < 4; n++)
        {
            setbox(locat + shapes[shape - 1][orival - 1][n][0], i + shapes[shape - 1][orival - 1][n][1], col, 1);
        }
        tempx = locat;
        tempy = i;
    }
    else
    {
        resetsignal = 1;
        resetit;
    }
}
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    displayshape(1);
    refresh();
    glutSwapBuffers();
}
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 5 * matrix_width, 0, 100);
}
void timer(int a)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 130, timer, 0);
}
int main(int argc, char **argv)
{
    col = gennum();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(matrix_width * 25, 500);
    glutInitWindowPosition(500, 100);
    glutCreateWindow("Tetris");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return 0;
}