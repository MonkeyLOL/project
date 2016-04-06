#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "SOIL.h"

class Rock : public SceneObject
{
public:
    Rock();
    ~Rock();
    float Radius() const;
    glm::vec3 Position() const;

    void die(float life);
    float getLife();
    void setLife(float l);

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    float speed_;
    float life_;
    float armor_;

    int list_id;
    float radius;
    glm::vec3 position_;
    int random;
    int rand2;
    double x;

};
