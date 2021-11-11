#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/time.h>
#include <GL/glut.h>
#include<stdbool.h>
#define padding 5.99
int8_t hello[20][10] = {0};
float colors [1][3]={{0, 0.003921569*108,0}};
void renderbox(float x, float y, int size)
{
    //bottom box
    glBegin(GL_POLYGON);
    glColor3f(colors,colors[0][1],0);
    glVertex2f(x, y);
    glVertex2f(x + size, y);
    glVertex2f(x + size - size /padding, y + size /padding);
    glVertex2f(x + size /padding, y + size /padding);
    glEnd();
    //left box
    glBegin(GL_POLYGON);
    glColor3f(0, 0.003921569*215, 0);
    glVertex2f(x, y);
    glVertex2f(x, y + size);
    glVertex2f(x + size /padding, y + size - size /padding);
    glVertex2f(x + size /padding, y + size /padding);
    glEnd();
    //top box
    glBegin(GL_POLYGON);
    glColor3f(0.592156863, 1, 0.592156863);
    glVertex2f(x, y + size);
    glVertex2f(x + size, y + size);
    glVertex2f(x + size - size /padding, y + size - size /padding);
    glVertex2f(x + size /padding, y + size - size /padding);
    glEnd();
    //right box
    glBegin(GL_POLYGON);
    glColor3f(0, 0.003921569*215, 0);
    glVertex2f(x + size, y);
    glVertex2f(x + size, y + size);
    glVertex2f(x + size - size /padding, y + size - size /padding);
    glVertex2f(x + size - size /padding, y + size /padding);
    glEnd();
    //center box
    glBegin(GL_POLYGON);
    // glColor3f(0, 0.9, 0);
    glColor3f(0, 0.003921569*240, 0);
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
