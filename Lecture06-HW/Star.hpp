
#pragma once
#include "MObject.h"
#include <GLFW/glfw3.h>

class Star : public MObject
{
public:

    Star(float x, float y, float size, float red, float green, float blue);

    void update() override;
    void render() override;

private:
    float _x;   
    float _y;    
    float _size;
    float _red; 
    float _green;
    float _blue; 
};