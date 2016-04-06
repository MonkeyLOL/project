#pragma once

#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "SOIL.h"
#include "Bullet.hpp"
#include "Input.hpp"

class SpaceShip : public SceneObject
{
public:
    SpaceShip();
    ~SpaceShip();

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();

    void die(float life);
    float getLife();
    void setLife(float l);

    int getScores();
    void addScores(int score);


    float Radius();
    glm::vec3 Position();

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    GLuint texture;
    float speed_;
    float life_;
    float armor_;
    int scores_;
    glm::vec3 position;
    float radius;
    int list_id;
    std::string Resources=resources + "spaceship.jpg";
};

