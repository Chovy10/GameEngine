#include <GLFW/glfw3.h>
#include <iostream>
#include "MSList.h"
#include "Star.hpp"
#include <cstdlib> 
#include <stdexcept>
#include <ctime>  


const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 768;

MSList<Star*> starList; 


void errorCallback(int error, const char* description)
{
    std::cerr << "\033[1;31mGLFW Error: " << description << "\033[0m" << std::endl;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


void drawStar(float x, float y, float size, float red, float green, float blue)
{
    glBegin(GL_TRIANGLES);

  
    glColor3f(red, green, blue);

    glVertex2f(0.0f, -0.04f);
    glVertex2f(-0.08f, 0.03f);
    glVertex2f(0.08f,0.03f);


    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f,0.01f);
    glVertex2f(0.06f,-0.08);
    glVertex2f(0.0f,-0.04f);


    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.01f);
    glVertex2f(-0.06f, -0.08f);
    glVertex2f(0.0f, -0.04f);

   

    glEnd();
}


void createRandomStars()
{
    const int numStars = 300;

    
    srand(time(nullptr));

  
    while (starList.get_size() > 0)
    {
        delete starList[0]; 
    }

 
    for (int i = 0; i < numStars; ++i)
    {
       
        float x = static_cast<float>(rand() % WINDOW_WIDTH);
        float y = static_cast<float>(rand() % WINDOW_HEIGHT);
        float size = static_cast<float>(rand() % 20 + 5); 

     
        float red = static_cast<float>(rand()) / RAND_MAX;
        float green = static_cast<float>(rand()) / RAND_MAX;
        float blue = static_cast<float>(rand()) / RAND_MAX;

        
        Star* newStar = new Star(x, y, size, red, green, blue);
        starList.add(newStar);
    }
}


void initializeOpenGL()
{
  
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Stars", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

  
    glfwMakeContextCurrent(window);
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);

 
    createRandomStars();

 
    while (!glfwWindowShouldClose(window))
    {
    
        glClear(GL_COLOR_BUFFER_BIT);

      
        for (int i = 0; i < starList.get_size(); ++i)
        {
            Star* star = starList[i];
        }

      
        glfwSwapBuffers(window);

       
        glfwPollEvents();
    }

   
    glfwTerminate();
}

int main()
{
    initializeOpenGL();
    return 0;
}