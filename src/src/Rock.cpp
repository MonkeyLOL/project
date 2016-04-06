
#include "Rock.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

Rock::Rock()
{
  x = 0;
  srand(time(0));
  random = rand()%40 - 20;
  rand2 = rand()%20;

  if (rand2 > 15){
    radius = 1.0;
    life_ = 20;
  }
  else{
    radius = 0.5;
    life_ = 10;
  }
  position_ = glm::vec3(random, 0.0f, -100.0f);

  privateInit();
}

Rock::~Rock()
{
}

void Rock::privateInit()
{

    GLuint tex_2d = SOIL_load_OGL_texture("/home/tony/Desktop/project/src/Resources/rock.jpg",
                                   SOIL_LOAD_AUTO,
                                   SOIL_CREATE_NEW_ID,
                                   SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
    if( 0 == tex_2d ) printf( "SOIL loading error: '%s'\n", SOIL_last_result() );

    glBindTexture(GL_TEXTURE_2D, tex_2d);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  list_id = glGenLists(1);
  float z = rand2/4 - 2;

  glNewList(list_id, GL_COMPILE);

  glBegin(GL_QUADS);

   glColor3f( 0.0, 0.0, 0.0 ); glVertex3f(  position_[0] + radius, position_[1] - radius, position_[2] - radius + z);
   glColor3f( 0.0, 0.0, 1.0 ); glVertex3f(  position_[0] + radius, position_[1] + radius, position_[2] - radius + z);
   glColor3f( 1.0, 0.0, 1.0 ); glVertex3f(  position_[0] - radius, position_[1] + radius, position_[2] - radius + z);
   glColor3f( 0.0, 1.0, 0.0 ); glVertex3f(  position_[0] - radius, position_[1] - radius, position_[2] - radius + z);


   glColor3f( 1.0, 1.0, 0.0 ); glVertex3f(  position_[0] + radius, position_[1] - radius, position_[2] + radius + z);
   glColor3f( 1.0, 1.0, 1.0 ); glVertex3f(  position_[0] + radius, position_[1] + radius, position_[2] + radius + z);
   glColor3f( 1.0, 0.0, 1.0 ); glVertex3f(  position_[0] - radius, position_[1] + radius, position_[2] + radius + z);
   glColor3f( 1.0, 0.0, 0.0 ); glVertex3f(  position_[0] - radius, position_[1] - radius, position_[2] + radius + z);

   glColor3f( 0.0, 1.0, 0.0 ); glVertex3f( position_[0] + radius, position_[1] - radius, position_[2] - radius + z);
   glColor3f( 0.0, 1.0, 1.0 ); glVertex3f( position_[0] + radius, position_[1] + radius, position_[2] - radius + z);
   glColor3f( 1.0, 1.0, 1.0 ); glVertex3f( position_[0] + radius, position_[1] + radius, position_[2] + radius + z);
   glColor3f( 1.0, 1.0, 0.0 ); glVertex3f( position_[0] + radius, position_[1] - radius, position_[2] + radius + z);

   glColor3f( 1.0, 0.0, 0.0 ); glVertex3f( position_[0] - radius, position_[1] - radius, position_[2] + radius + z);
   glColor3f( 1.0, 0.0, 1.0 ); glVertex3f( position_[0] - radius, position_[1] + radius, position_[2] + radius + z);
   glColor3f( 0.0, 0.0, 1.0 ); glVertex3f( position_[0] - radius, position_[1] + radius, position_[2] - radius + z);
   glColor3f( 0.0, 0.0, 0.0 ); glVertex3f( position_[0] - radius, position_[1] - radius, position_[2] - radius + z);

   glColor3f( 1.0, 1.0, 1.0 ); glVertex3f(  position_[0] + radius, position_[1] + radius, position_[2] + radius + z);
   glColor3f( 0.0, 1.0, 1.0 ); glVertex3f(  position_[0] + radius, position_[1] + radius, position_[2] - radius + z);
   glColor3f( 0.0, 0.0, 1.0 ); glVertex3f(  position_[0] - radius, position_[1] + radius, position_[2] - radius + z);
   glColor3f( 1.0, 0.0, 1.0 ); glVertex3f(  position_[0] - radius, position_[1] + radius, position_[2] + radius + z);

   glColor3f( 0.0, 1.0, 0.0 ); glVertex3f(  position_[0] + radius, position_[1] - radius, position_[2] - radius + z);
   glColor3f( 1.0, 1.0, 0.0 ); glVertex3f(  position_[0] + radius, position_[1] - radius, position_[2] + radius + z);
   glColor3f( 1.0, 0.0, 0.0 ); glVertex3f(  position_[0] - radius, position_[1] - radius, position_[2] + radius + z);
   glColor3f( 0.0, 0.0, 0.0 ); glVertex3f(  position_[0] - radius, position_[1] - radius, position_[2] - radius + z);
   glEnd();

   glEndList();
}

void Rock::privateRender()
{
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat lightpos[] = {10, 10, 10, 1.0};
  GLfloat mat_ambient[] = {0.5,0.5,0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);

  glm::vec3 move1 = glm::vec3(0.0f, 0.0f, 0.02f);
  glm::vec3 move2 = glm::vec3(sin(x)/30, 0.0f, 0.02f);

  if (rand2 > 15){
    matrix_ = glm::translate(matrix_, move1);
    position_ += move1;
  }
  else{
    matrix_ = glm::translate(matrix_, move2);
    position_ += move2;

    x += 0.02;
    if (x > 2*M_PI) x = 0;
  }
  glCallList(list_id);

  glDisable(GL_LIGHT0);
  glDisable(GL_LIGHTING);
}

void Rock::privateUpdate()
{


}

float Rock::Radius() const
{
  return radius;
}

glm::vec3 Rock::Position() const
{
  return position_;
}

void Rock::die(float life)
{
  life_ -= life;
}

float Rock::getLife()
{
  return life_;
}

void Rock::setLife(float li)
{
  life_ = li;
}



