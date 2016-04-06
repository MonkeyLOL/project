#include "BattleField.hpp"


BattleField::BattleField()
{
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
  // texturing
    texture=SOIL_load_OGL_texture(Resources.data(),
                              SOIL_LOAD_AUTO,
                              SOIL_CREATE_NEW_ID,
                              SOIL_FLAG_MIPMAPS|SOIL_FLAG_INVERT_Y|SOIL_FLAG_NTSC_SAFE_RGB|SOIL_FLAG_COMPRESS_TO_DXT);
    if (0==texture)
    {
        std::cout << "Soil load error: " << SOIL_last_result() << std::endl;
    }
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    for(int i=0;i<z_;i++)
    {
        for(int j=0;j<x_;j++)
        {
            vertexArray_.push_back(glm::vec3(j*10.0f,0,i*10.0f));
            texCoordArray_.push_back(glm::vec2((float)j/(x_ - 1), (float)i/(z_ -1)));
        }
    }

    for (int x=0;x<z_;x++)
    {
        for(int y=0;y<x_;y++)
        {
            indexArray_.push_back(y+x*x_);
            indexArray_.push_back(y + x_ + x*x_);
        }
        indexArray_.push_back(5000000);
    }
}


void BattleField::privateRender()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    GLfloat lightpos[] = {10, 10, 10, 1.0};
    GLfloat mat_ambient[] = {0.0,0.5,0.3};
    glLightfv(GL_LIGHT1, GL_POSITION, lightpos);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_ambient);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
      glNormal3f( 0.0f, 1.0f, 0.0f);
      glTexCoord2f ( 0, 1 ); glVertex3f(-170, -20,  130);
      glTexCoord2f ( 0, 0 ); glVertex3f( 170, -20,  130);
      glTexCoord2f ( 1, 0 ); glVertex3f( -170,  -20,  -5120);
      glTexCoord2f ( 1, 1 ); glVertex3f(170, -20,  -5120);
    glEnd();
}


void BattleField::privateUpdate()
{
}

