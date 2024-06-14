#pragma once
#include <GLFW/glfw3.h>

// Base class
class Object {
public:
    int x, y, width, height;

    Object(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    virtual void OnCollisionEnter(Object& other) {
        // Define this function in derived classes
    }

    bool CheckCollision(Object& other) {
        // Axis-Aligned Bounding Box (AABB) collision detection
        return (x < other.x + other.width &&
            x + width > other.x &&
            y < other.y + other.height &&
            y + height > other.y);
    }

    virtual void Render() {
        // Define this function in derived classes
    }

    void RenderBorder() {
        // Base class has no border rendering
    }
};

// Derived classes
class Player : public Object {
public:
    Player(int x, int y, int size)
        : Object(x, y, size, size) {}

    void OnCollisionEnter(Object& other) override {
        // Player-specific collision logic
    }

    void Render() override {
        // Render Player specifics
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();

        // Render Player border (only for the Player)
        glLineWidth(3.0f); // Set border thickness to 3 units
        glColor3f(0.0f, 0.0f, 0.0f); // Black color for the border
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }
};

class EnemyBlock : public Object {
public:
    EnemyBlock(int x, int y, int width, int height)
        : Object(x, y, width, height) {}

    void OnCollisionEnter(Object& other) override {
        // EnemyBlock-specific collision logic
    }

    void Render() override {
        // Render EnemyBlock specifics
        glColor3f(0.0f, 1.0f, 0.0f); // Green color
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }
};

class Floor : public Object {
public:
    Floor(int y)
        : Object(0, y, 800, 10) {} // Assume a wide floor

    void OnCollisionEnter(Object& other) override {
        // Floor-specific collision logic
    }

    void Render() override {
        // Render Floor specifics
        glColor3f(1.0f, 0.78f, 0.06f); // Yellow color
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }
};

class Star : public Object {
public:
    Star(int x, int y, int size)
        : Object(x, y, size, size) {}

    void OnCollisionEnter(Object& other) override {
        // Star-specific collision logic
    }

    void Render() override {
        // Render Star specifics
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
        glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width, y + height);
        glVertex2f(x, y + height);
        glEnd();
    }

    int PhysicsAABB(Object A, Object B)
    {
        return 0;
    }


};
