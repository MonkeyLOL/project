#include "GameManager.hpp"
//#include "boost/shared_ptr.hpp"
#include <memory>


GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
  // Set default OpenGL states
  glEnable(GL_CULL_FACE);

  // Adding the camera to the scene
  cam_.reset(new Camera());

  spaceship_.reset(new SpaceShip());
  this->addSubObject(spaceship_);

  bf_.reset(new BattleField());
  this->addSubObject(bf_);

}

void GameManager::privateRender()
{
  float life;
  float rocklife;

  for(int i = 0; i < bulletsPlayer_.size();i++)
    if(bulletsPlayer_[i]->Position()[2] < -1000)
    {
      this->removeSubObject(bulletsPlayer_[i]);
      bulletsPlayer_.erase(bulletsPlayer_.begin()+i);
    }

   for(int i = 0; i < bullets_.size();i++)
    if(bullets_[i]->Position()[2] > 50)
    {
      this->removeSubObject(bullets_[i]);
      bullets_.erase(bullets_.begin()+i);
    }

    for (int i = 0; i < rocks_.size(); i++)
    if (Collision(rocks_[i]->Radius(), spaceship_->Radius(), rocks_[i]->Position(), spaceship_->Position()))
    {
      this->removeSubObject(rocks_[i]);
      rocks_.erase(rocks_.begin()+i);

      spaceship_->setLife(0);
      this->removeSubObject(spaceship_);
    }

  for (int i = 0; i < bullets_.size(); i++)
    if (Collision(bullets_[i]->Radius(), spaceship_->Radius(), bullets_[i]->Position(), spaceship_->Position()))
    {
      this->removeSubObject(bullets_[i]);
      bullets_.erase(bullets_.begin()+i);

      spaceship_->die(10);
      life = spaceship_->getLife()-10;
      spaceship_->setLife(life);

      spaceship_->addScores(-50);


      if (spaceship_->getLife() <= 0){
    this->removeSubObject(spaceship_);
      }
    }

  for (int i = 0; i < rocks_.size(); i++)
      for (int j = 0; j < bulletsPlayer_.size(); j++)
          if (Collision(bulletsPlayer_[j]->Radius(), rocks_[i]->Radius(), bulletsPlayer_[j]->Position(), rocks_[i]->Position()))
          {
              this->removeSubObject(bulletsPlayer_[j]);
              bulletsPlayer_.erase(bulletsPlayer_.begin()+i);
              rocks_[i]->die(2);
              rocklife = rocks_[i]->getLife()-2;
              rocks_[i]->setLife(rocklife);
              spaceship_->addScores(100);
              if (rocks_[i]->getLife() <= 0) {
                  this->removeSubObject(rocks_[i]);
                  rocks_.erase(rocks_.begin()+i);
              }

          }
  // Nothing to render
}

void GameManager::privateUpdate()
{
  // Instead of adding alle objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix.
  this->matrix_ = cam_->getMatrix();


}

std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}

std::shared_ptr<SpaceShip> GameManager::getShip()
{
    return spaceship_;
}

void GameManager::addRock()
{
    std::shared_ptr<Rock> rock_;
    rock_.reset(new Rock());
    this->addSubObject(rock_);
    rocks_.push_back(rock_);
    addBullet();

}


void GameManager::addBullet()
{
  for (int i; i < rocks_.size(); i++){
      std::shared_ptr<Bullet> bullet_;
      glm::vec3 dir(0,0,0.1);
      bullet_.reset(new Bullet());
      bullet_->SetPosition(rocks_[i]->Position());
      bullet_->SetDirection(dir);
      this->addSubObject(bullet_);
      bullets_.push_back(bullet_);
  }
}

void GameManager::addBulletPlayer()
{
    std::shared_ptr<Bullet> bullet_;
    glm::vec3 dir(0,0,-1);
    bullet_.reset(new Bullet());
    bullet_->SetPosition(spaceship_->Position());
    bullet_->SetDirection(dir);
    this->addSubObject(bullet_);
    bulletsPlayer_.push_back(bullet_);
}

bool GameManager::Collision(float radius1, float radius2, glm::vec3 position1, glm::vec3 position2)
{
  float d = glm::length(position1-position2);
  if (d <= radius1+radius2) return true;
  return false;
}






