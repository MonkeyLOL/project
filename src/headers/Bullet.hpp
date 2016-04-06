#pragma once

#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class Bullet : public SceneObject
{
public:
    Bullet();
    ~Bullet();

    void SetPosition(glm::vec3 pos);
    float Radius();
    glm::vec3 Position();
    void SetDirection(glm::vec3 dir);



protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    int list_id;

    glm::vec3 position;
    float radius;
    glm::vec3 direction;



};
