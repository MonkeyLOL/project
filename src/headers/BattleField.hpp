#pragma once

#include <GL/freeglut.h>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include "SOIL.h"
#include "Input.hpp"
#include "SceneObject.hpp"
#include "glm/glm.hpp"

class BattleField : public SceneObject
{
public:
    BattleField();
    ~BattleField();

protected:
    virtual void privateInit();
    virtual void privateRender();
    virtual void privateUpdate();

private:
    GLuint texture;
    std::vector< glm::vec3 > vertexArray_; // Maybe two-dim vector and several arrays
    std::vector <unsigned int> indexArray_; // normal array.
    std::vector<glm::vec2> texCoordArray_; // texture coord array
    float z_=512.0f;
    float x_=32.0f;
    std::string Resources = resources+"background.jpg";
};

