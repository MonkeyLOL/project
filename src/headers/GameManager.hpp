#pragma once

//#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Camera.hpp"
#include "Rock.hpp"
#include "Bullet.hpp"

#include <memory>

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

class GameManager : public SceneObject
{
    public:
        GameManager();
        ~GameManager();

    std::shared_ptr<Camera> getCam();
    std::shared_ptr<SpaceShip> getShip();

    void addRock();
    void addBullet();
    void addBulletPlayer();
    bool Collision(float radius1, float radius2, glm::vec3 position1, glm::vec3 position2);



  protected:
    virtual void privateInit();
    virtual void privateRender();
    virtual void privateUpdate();

    private:
    std::shared_ptr<BattleField> bf_;
    std::shared_ptr<SpaceShip> spaceship_;
    std::shared_ptr<Camera> cam_;
    std::vector< std::shared_ptr<Rock> > rocks_;
    std::vector< std::shared_ptr<Bullet> > bullets_;
    std::vector< std::shared_ptr<Bullet> > bulletsPlayer_;
};

