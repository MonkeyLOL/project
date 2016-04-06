
#include "SpaceShip.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>


SpaceShip::SpaceShip()
{
    radius = 1.0f;
    position = glm::vec3(0.0f, 0.0f, 4.0f);
    life_ = 100;
    scores_ = 0;
}

SpaceShip::~SpaceShip()
{
}


void SpaceShip::privateInit()
{
    texture = SOIL_load_OGL_texture(Resources.data(),
                                   SOIL_LOAD_AUTO,
                                   SOIL_CREATE_NEW_ID,
                                   SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    if( 0 == texture ) printf( "SOIL loading error: '%s'\n", SOIL_last_result() );

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    list_id = glGenLists(1);
    glNewList(list_id, GL_COMPILE);

     glBegin(GL_QUADS);
     glNormal3f( 0.0f, 0.0f, 1.0f);
     glTexCoord2f(0.0f, 0.0f); glVertex3f(  position[0] + 0.5, position[1] - 0.5, position[2] - 0.5 );
     glTexCoord2f(1.0f, 0.0f); glVertex3f(  position[0] + 0.5, position[1] + 0.5, position[2] - 0.5 );
     glTexCoord2f(1.0f, 1.0f); glVertex3f(  position[0] - 0.5, position[1] + 0.5, position[2] - 0.5 );
     glTexCoord2f(0.0f, 1.0f); glVertex3f(  position[0] - 0.5, position[1] - 0.5, position[2] - 0.5 );

     glNormal3f( 0.0f, 0.0f, -1.0f);
     glTexCoord2f(0.0f, 0.0f); glVertex3f(  position[0] + 0.5, position[1] - 0.5, position[2] + 0.5 );
     glTexCoord2f(1.0f, 0.0f); glVertex3f(  position[0] + 0.5, position[1] + 0.5, position[2] + 0.5 );
     glTexCoord2f(1.0f, 1.0f); glVertex3f(  position[0] - 0.5, position[1] + 0.5, position[2] + 0.5 );
     glTexCoord2f(0.0f, 1.0f); glVertex3f(  position[0] - 0.5, position[1] - 0.5, position[2] + 0.5 );

     glNormal3f( 1.0f, 0.0f, 0.0f);
     glTexCoord2f(0.0f, 0.0f); glVertex3f( position[0] + 0.5, position[1] - 0.5, position[2] - 0.5 );
     glTexCoord2f(1.0f, 0.0f); glVertex3f( position[0] + 0.5, position[1] + 0.5, position[2] - 0.5 );
     glTexCoord2f(1.0f, 1.0f); glVertex3f( position[0] + 0.5, position[1] + 0.5, position[2] + 0.5 );
     glTexCoord2f(0.0f, 1.0f); glVertex3f( position[0] + 0.5, position[1] - 0.5, position[2] + 0.5 );

     glNormal3f( -1.0f, 0.0f, 0.0f);
     glTexCoord2f(0.0f, 0.0f); glVertex3f( position[0] - 0.5, position[1] - 0.5, position[2] + 0.5 );
     glTexCoord2f(1.0f, 0.0f); glVertex3f( position[0] - 0.5, position[1] + 0.5, position[2] + 0.5 );
     glTexCoord2f(1.0f, 1.0f); glVertex3f( position[0] - 0.5, position[1] + 0.5, position[2] - 0.5 );
     glTexCoord2f(0.0f, 1.0f); glVertex3f( position[0] - 0.5, position[1] - 0.5, position[2] - 0.5 );

     glNormal3f( 0.0f, 1.0f, 0.0f);
     glTexCoord2f(0.0f, 0.0f); glVertex3f( position[0] + 0.5, position[1] + 0.5, position[2] + 0.5 );
     glTexCoord2f(1.0f, 0.0f); glVertex3f( position[0] + 0.5, position[1] + 0.5, position[2] - 0.5 );
     glTexCoord2f(1.0f, 1.0f); glVertex3f( position[0] - 0.5, position[1] + 0.5, position[2] - 0.5 );
     glTexCoord2f(0.0f, 1.0f); glVertex3f( position[0] - 0.5, position[1] + 0.5, position[2] + 0.5 );

     glNormal3f( 0.0f, -1.0f, 0.0f);
     glTexCoord2f(0.0f, 0.0f); glVertex3f( position[0] + 0.5, position[1] - 0.5, position[2] - 0.5 );
     glTexCoord2f(1.0f, 0.0f); glVertex3f( position[0] + 0.5, position[1] - 0.5, position[2] + 0.5 );
     glTexCoord2f(1.0f, 1.0f); glVertex3f( position[0] - 0.5, position[1] - 0.5, position[2] + 0.5 );
     glTexCoord2f(0.0f, 1.0f); glVertex3f( position[0] - 0.5, position[1] - 0.5, position[2] - 0.5 );
     glEnd();
    glEndList();
}

void SpaceShip::privateRender()
{

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat lightpos[] = {10, 10, 10, 1.0};
  GLfloat mat_ambient[] = {0.5,0.5,0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);

  glCallList(list_id);

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void SpaceShip::privateUpdate()
{
}

void SpaceShip::moveRight()
{
    if ( position[0] < 50 ){
        glm::vec3 v = glm::vec3(0.03f, 0.0f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }

}
void SpaceShip::moveLeft()
{
    if ( position[0] > -50 ){
        glm::vec3 v = glm::vec3(-0.03f, 0.0f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }
}

void SpaceShip::moveUp()
{
    if ( position[1] < 3 ){
        glm::vec3 v = glm::vec3(0.0f, 0.01f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }
}
void SpaceShip::moveDown()
{
    if ( position[1] > -3 ){
        glm::vec3 v = glm::vec3(0.0f, -0.01f, 0.0f);
        matrix_ = glm::translate(matrix_, v);

        position += v;
    }
}


float SpaceShip::Radius()
{
    return radius;
}

glm::vec3 SpaceShip::Position()
{
    return position;
}

void SpaceShip::die(float life)
{
  life_ -= life;
}

float SpaceShip::getLife()
{
  return life_;
}

void SpaceShip::setLife(float l)
{
  life_ = l;
}

int SpaceShip::getScores()
{
  return scores_;
}

void SpaceShip::addScores(int score)
{
  scores_ += score;
}
