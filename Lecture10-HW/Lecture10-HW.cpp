#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const float SUN_RADIUS = 150.0f;
const float INNER_CIRCLE_RADIUS = 100.0f;
const float INNER_CIRCLE_RADIUS_2 = 25.0f; // 추가된 내부 원의 반지름
const float ORBIT_RADIUS = 400.0f;
const float ORBIT_SPEED = 2 * M_PI / 30.0f; // 30 seconds for one orbit
const float ROTATION_SPEED = 2 * M_PI / 30.0f; // 30 seconds for one rotation
const float EARTH_RADIUS = 50.0f; // Earth's radius
const float EARTH_ORBIT_SPEED = 2 * M_PI / 60.0f; // 60 seconds for one orbit (1 minute)
const float MOON_ROTATION_SPEED = 2 * M_PI / 3.0f; // 3 seconds for one rotation
const float MOON_ORBIT_SPEED = 2 * M_PI / 3.0f; // 3 seconds for one orbit
const float MOON_ORBIT_RADIUS = 15.00;

void error_callback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void drawSun(float radius)
{
    // Draw the sun
    glColor3f(255.0f / 255.0f, 217.0f / 255.0f, 102.0f / 255.0f); // Orange color with full opacity

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f); // Center of the sun
    for (int i = 0; i <= 360; ++i) // 360도를 1도 간격으로
    {
        float angle = i * (M_PI / 180.0f); // 각도를 라디안으로 변환
        float x = radius * cos(angle); // x 좌표 계산
        float y = radius * sin(angle); // y 좌표 계산
        glVertex2f(x, y); // 해당 점 추가
    }
    glEnd();

    glColor3f(204.0f / 255.0f, 107.0f / 255.0f, 36.0f / 255.0f); // Sun outline color
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; ++i)
    {
        float angle = i * (M_PI / 180.0f);
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawInnerCircles(float time)
{
    // Draw the first inner circle (white)
    glColor3f(255.0f / 255.0f, 230.0f / 255.0f, 153.0f / 255.0f); // White color with full opacity
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(-INNER_CIRCLE_RADIUS / 2.0f, 0.0f); // Center of the first inner circle (left side)
    for (int i = 0; i <= 360; ++i) // 360도를 1도 간격으로
    {
        float angle = i * (M_PI / 180.0f); // 각도를 라디안으로 변환
        float x = INNER_CIRCLE_RADIUS * cos(angle) - INNER_CIRCLE_RADIUS / 2.0f; // x 좌표 계산
        float y = INNER_CIRCLE_RADIUS * sin(angle); // y 좌표 계산
        glVertex2f(x, y); // 해당 점 추가
    }
    glEnd();

    // Draw the second inner circle (gray)
    glColor3f(255.0f / 255.0f, 192.0f / 255.0f, 0.0f); // Gray color with full opacity
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(INNER_CIRCLE_RADIUS / 2.0f, -INNER_CIRCLE_RADIUS / 2.0f); // Center of the second inner circle (bottom right)
    for (int i = 0; i <= 360; ++i) // 360도를 1도 간격으로
    {
        float angle = i * (M_PI / 180.0f); // 각도를 라디안으로 변환
        float x = INNER_CIRCLE_RADIUS_2 * cos(angle) + INNER_CIRCLE_RADIUS / 2.0f; // x 좌표 계산
        float y = INNER_CIRCLE_RADIUS_2 * sin(angle) - INNER_CIRCLE_RADIUS / 2.0f; // y 좌표 계산
        glVertex2f(x, y); // 해당 점 추가
    }
    glEnd();
}

void drawEarth(float time)
{
    // Draw the Earth (rectangle)
    glColor3f(91.0f / 255.f, 155.0f / 255.0f, 213.0f / 255.0f); // Earth color
    glBegin(GL_QUADS);
    float angle = time * ROTATION_SPEED;
    float x = EARTH_RADIUS * cos(angle);
    float y = EARTH_RADIUS * sin(angle);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x + 10, y - 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x - 10, y + 10);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - 10, y - 10);
    glVertex2f(x + 10, y - 10);
    glVertex2f(x + 10, y + 10);
    glVertex2f(x - 10, y + 10);
    glEnd();
}


void drawStars(float scaleFactor, float moveFactor, float time)
{
    glColor3f(255.0f, 242.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);
    glVertex2f(-0.8f * scaleFactor, (0.3f + moveFactor) * scaleFactor);
    glVertex2f(0.8f * scaleFactor, (0.3f + moveFactor) * scaleFactor);

    glVertex2f(0.0f * scaleFactor, (1.0f + moveFactor) * scaleFactor);
    glVertex2f(0.6f * scaleFactor, (-0.8f + moveFactor) * scaleFactor);
    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);

    glVertex2f(0.0f * scaleFactor, (1.0f + moveFactor) * scaleFactor);
    glVertex2f(-0.6f * scaleFactor, (-0.8f + moveFactor) * scaleFactor);
    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);
    glEnd();

    glColor3f(45.0f / 255.0f, 45.0f / 255.0f, 40.0f / 255.0f); // Star outline color
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);
    glVertex2f(-0.8f * scaleFactor, (0.3f + moveFactor) * scaleFactor);
    glVertex2f(0.8f * scaleFactor, (0.3f + moveFactor) * scaleFactor);
    glVertex2f(0.0f * scaleFactor, (1.0f + moveFactor) * scaleFactor);
    glVertex2f(0.6f * scaleFactor, (-0.8f + moveFactor) * scaleFactor);
    glVertex2f(0.0f * scaleFactor, (-0.4f + moveFactor) * scaleFactor);
    glVertex2f(-0.6f * scaleFactor, (-0.8f + moveFactor) * scaleFactor);
    glEnd();
}

int main()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sun System", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400, 400, -300, 300, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_BLEND); // Enable blending for transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Set blending function

    float time = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
        glClear(GL_COLOR_BUFFER_BIT);

        glLoadIdentity();
        glTranslatef(0.0f, 0.0f, 0.0f); // Move to the center of the screen

        // Draw the sun
        drawSun(SUN_RADIUS);

        // Draw the inner circles with rotation
        glPushMatrix(); // Save the current matrix
        glRotatef(time * ROTATION_SPEED * (180.0f / M_PI), 0.0f, 0.0f, 1.0f); // Rotate the inner circles
        drawInnerCircles(time);
        glPopMatrix(); // Restore the
        // Draw the Earth with rotation and orbit
        glPushMatrix(); // Save the current matrix
        glRotatef(time * ROTATION_SPEED * (180.0f / M_PI), 0.0f, 0.0f, 1.0f); // Rotate the Earth
        glTranslatef(ORBIT_RADIUS, 0.0f, 0.0f); // Translate to the orbit radius
        glRotatef(time * EARTH_ORBIT_SPEED * (180.0f / M_PI), 0.0f, 0.0f, 1.0f); // Orbit the Earth around the Sun
        drawEarth(time);
        glPopMatrix(); // Restore the saved matrix

        glPushMatrix(); // Save the current matrix
        glRotatef(time * ROTATION_SPEED * (180.0f / M_PI), 0.0f, 0.0f, 1.0f); // Rotate the Moon
        glTranslatef(ORBIT_RADIUS + MOON_ORBIT_RADIUS, 0.0f, 0.0f); // Translate to the Moon's orbit radius
        glRotatef(time * MOON_ORBIT_SPEED * (180.0f / M_PI), 0.0f, 0.0f, 1.0f); // Orbit the Moon around the Earth
        drawStars(1.0f, 0.0f, time); // Draw the Moon
        glPopMatrix(); // Restore the saved matrix

        glfwSwapBuffers(window);
        glfwPollEvents();

        // Update time
        time += 1.0f / 60.0f; // Assuming 60 FPS
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

