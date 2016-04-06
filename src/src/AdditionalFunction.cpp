#include "AdditionalFunction.hpp"

additionalFunction::additionalFunction()
{

}

additionalFunction::~additionalFunction()
{

}

void additionalFunction::drawText(const char *text, int length, int x, int y)
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0,700,0,700,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x,y);
    for(int i = 0; i<length;i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15,(int)text[i]);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}

