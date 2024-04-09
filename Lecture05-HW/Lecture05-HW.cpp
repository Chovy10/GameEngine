#pragma comment(lib, "Opengl32.lib")

#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float moveFactor = 0.0f;
float scaleFactor = 1.0f;
double lastX = 0.0;
double lastY = 0.0;
bool isDragging = false;
bool isScaling = false;
double starCenterX = 0.0;


void errorCallback(int error, const char* description)
{
    std::cerr << "GLFW Error: " << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (isDragging)
    {
        moveFactor += (ypos - lastY) * 0.01f;
        lastX = xpos;
        lastY = ypos;
    }

    if (isScaling)
    {
        double deltaX = xpos - lastX;
        scaleFactor += (xpos - lastX) * 0.01f;
        starCenterX += deltaX * 0.005f;
        lastX = xpos;
    }
}


void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            isDragging = true;
            glfwGetCursorPos(window, &lastX, &lastY);
        }
        else if (action == GLFW_RELEASE)
        {
            isDragging = false;
        }
    }

    else if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            isScaling = true;
            glfwGetCursorPos(window, &lastX, nullptr);
        }
        else if (action == GLFW_RELEASE)
        {
            isScaling = false;
        }
    }


}

int render()
{
    glBegin(GL_TRIANGLES);

    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);
    glVertex2f(-0.8f * scaleFactor, (0.3f + moveFactor) * scaleFactor);
    glVertex2f(0.8f * scaleFactor, (0.3f + moveFactor) * scaleFactor);


    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f * scaleFactor, (1.0f + moveFactor) * scaleFactor);
    glVertex2f(0.6f * scaleFactor, (-0.8f + moveFactor) * scaleFactor);
    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);


    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f * scaleFactor, (1.0f + moveFactor) * scaleFactor);
    glVertex2f(-0.6f * scaleFactor, (-0.8f + moveFactor) * scaleFactor);
    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);


    glEnd();

    return 0;
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
    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);



    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}