void display(){
   glClear(GL_COLOR_BUFFER_BIT);
   glLoadIdentity();
   glBegin(GL_POLYGON);
   glVertex2d(2,2);
   glVertex2d(-2,2);
   glVertex2d(-2,-2);
   glEnd();
   glutSwapBuffers();
}
void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, 500, 0, 500);
   glMatrixMode(GL_MODELVIEW);
}