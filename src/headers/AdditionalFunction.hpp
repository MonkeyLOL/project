#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Input.hpp"
#include "FpsCounter.hpp"
#include "GameManager.hpp"
#include "glm/glm.hpp"
#include <memory>

#include <iostream>
#include <sstream>


class additionalFunction
{
public:
    additionalFunction();
    ~additionalFunction();
    void drawText(const char *text, int length, int x, int y);
    void keyDown(unsigned char key, int x, int y);
    void addRock(int i);
};
