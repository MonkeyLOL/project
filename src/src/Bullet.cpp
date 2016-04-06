#include "Bullet.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Bullet::Bullet()
{
  radius = 0.5;

}

Bullet::~Bullet()
{
}

void Bullet::privateInit()
{
    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 1.0f, 0.0f );
    glColor3f( 0.0f, 0.0f, 0.0f );
    glVertex3f( position[0] + 0.1, position[1] - 0.1, position[2] );
    glVertex3f( position[0] + 0.1, position[1] + 0.1, position[2] );
    glVertex3f( position[0] - 0.1, position[1] + 0.1, position[2] );
    glVertex3f( position[0] - 0.1, position[1] - 0.1, position[2] );
    glEnd();
    glEndList();
}

void Bullet::privateRender()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightpos[] = {10, 10, 10, 1.0};
    GLfloat mat_ambient[] = {0.5,0.5,0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

    matrix_ = glm::translate(matrix_, direction);
    glCallList(list_id);

    position += direction;

    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void Bullet::privateUpdate()
{

}

void Bullet::SetPosition(glm::vec3 pos)
{
    position = pos;
    privateInit();
}

void Bullet::SetDirection(glm::vec3 dir)
{
    direction = dir;
    privateInit();
}


float Bullet::Radius()
{
    return radius;
}

glm::vec3 Bullet::Position()
{
    return position;
}



