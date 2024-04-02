#pragma comment(lib, "Opengl32.lib")
#include <GLFW/glfw3.h>
#include <iostream>


float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

double prevX = 0.0;
double prevY = 0.0;
bool isLeftMouseButtonPressed = false;


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        red = 1.0f;
        green = 0.0f;
        blue = 0.0f;
    }

    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        red = 0.0f;
        green = 1.0f;
        blue = 0.0f;
    }


    if (action == GLFW_RELEASE)
    {

        red = 0.0f;
        green = 0.0f;
        blue = 0.0f;
    }

}


void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    static double prevX = xpos;
    static double prevY = ypos;
    bool isStopped = (xpos == prevX && ypos == prevY);

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
    {
        red = 0.0f;
        green = 0.0f;
        blue = 1.0f;
    }

    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        red = 1.0f;
        green = 0.0f;
        blue = 1.0f;
    }



}




int main(void)
{

    if (!glfwInit())
        return -1;

    GLFWwindow* window;
    window = glfwCreateWindow(1280, 768, "MuSoeunEngine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    glfwMakeContextCurrent(window);


    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;


}