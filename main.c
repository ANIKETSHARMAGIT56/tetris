#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <GL/glut.h>
#include<stdbool.h>
#define padding 5.99
int8_t hello[20][10] = {0};
// i am using unsigned char becuse i only want to use 8 bit numbers and it char only uses 8 bits
unsigned char colors [3][5][3]={
    {
    // the green box
    {0,75,0}, //bottom
    {76,255,76}, //left
    {180,255,180}, //top
    {0,179,0}, //right
    {0,255,0}
    },
    {
    //red box
    {75,0,0}, //bottom
    {255,76,76}, //left
    {255,180,180}, //top
    {179,0,0}, //right
    {255,0,0} //center
    },
    {
    //red box
    {0,0,75}, //bottom
    {76,76,255}, //left
    {180,180,255}, //top
    {0,0,179}, //right
    {0,0,255} //center
    }};
void renderbox(float x, float y, int size)
{
    int color=0;
    //bottom box
    glBegin(GL_POLYGON);
    glColor3f(0.003921569*colors[color][0][0],0.003921569*colors[color][0][1],0.003921569*colors[color][0][2]);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size - size /padding, y + size /padding);
    glVertex2f(x + size /padding, y + size /padding);
    glEnd();
    //left box
    glBegin(GL_POLYGON);
    glColor3f(0.003921569*colors[color][1][0],0.003921569*colors[color][1][1],0.003921569*colors[color][1][2]);
    glVertex2f(x, y);
    glVertex2f(x, y + size);
    glVertex2f(x + size /padding, y + size - size /padding);
    glVertex2f(x + size /padding, y + size /padding);
    glEnd();
    //top box
    glBegin(GL_POLYGON);
    glColor3f(0.003921569*colors[color][2][0],0.003921569*colors[color][2][1],0.003921569*colors[color][2][2]);
    glVertex2f(x, y + size);
    glVertex2f(x + size, y + size);
    glVertex2f(x + size - size /padding, y + size - size /padding);
    glVertex2f(x + size /padding, y + size - size /padding);
    glEnd();
    //right box
    glBegin(GL_POLYGON);
    glColor3f(0.003921569*colors[color][3][0],0.003921569*colors[color][3][1],0.003921569*colors[color][3][2]);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x + size - size /padding, y + size - size /padding);
    glVertex2f(x + size - size /padding, y + size /padding);
    glEnd();
    //center box
    glBegin(GL_POLYGON);
    glColor3f(0.003921569*colors[color][4][0],0.003921569*colors[color][4][1],0.003921569*colors[color][4][2]);
    glVertex2f(x + size /padding, y + size /padding);
    glVertex2f(x + size /padding, y + size - size /padding);
    glVertex2f(x + size - size /padding, y + size - size /padding);
    glVertex2f(x + size - size /padding, y + size /padding);
    glEnd();
}
void setbox(int x,int y,int8_t value){
    hello[y][x]=value;
}
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DOUBLE);
    hello[1][1]=1;
    hello[1][2]=1;
    hello[1][3]=1;
    hello[2][2]=1;

    // glBegin(GL_POLYGON);
    for (int i = 0; i < 20; i++)
    {
        for (int s = 0; s < 10; s++)
        {
            if (hello[i][s] == 1)
            {
                renderbox(s * 5, i*5, 5);
            }
        }
    }

    // glEnd();
    glFlush();
}
void init()
{
    glClearColor(0.0, 0.9, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 50, 0, 100);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(250, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("simple");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
}
