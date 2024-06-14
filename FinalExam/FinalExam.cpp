#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// 사용자 정의 좌표 시스템 설정 함수
void coordinate(int left, int right, int bottom, int top) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -1, 1); // Bottom-left corner is (left, bottom)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

class Object {
protected:
    int x, y, width, height;

public:
    Object(int x, int y, int width, int height)
        : x(x), y(y), width(width), height(height) {}

    virtual void Render() const = 0;

    bool CheckCollision(const Object& other) const {
        return (x < other.x + other.width &&
            x + width > other.x &&
            y < other.y + other.height &&
            y + height > other.y);
    }

    virtual void OnCollisionEnter(Object& other) {
        // Define this function in derived classes
    }
};

class Player : public Object {
public:
    Player(int x, int y, int size)
        : Object(x, y, size, size) {}

    void Render() const override {
        glColor3f(1.0f, 0.0f, 0.0f); // Red color
        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();

        // Render Player border (only for the Player)
        glLineWidth(3.0f); // Set border thickness to 3 units
        glColor3f(0.0f, 0.0f, 0.0f); // Black color for the border
        glBegin(GL_LINE_LOOP);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();
    }
};

class Floor : public Object {
public:
    Floor(int y, int screenWidth)
        : Object(0, y, screenWidth, 100) {}

    void Render() const override {
        glColor3ub(255, 200, 15); // Yellow color (R:255, G:200, B:15)
        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();
    }
};

class EnemyBlock : public Object {
public:
    EnemyBlock(int x, int y, int width, int height)
        : Object(x, y, width, height) {}

    void Render() const override {
        glColor3f(0.0f, 1.0f, 0.0f); // Green color
        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();
    }
};

// 두 점 사이의 거리를 계산하는 함수
float calculateDistance(int x1, int y1, int x2, int y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

int main() {
    // GLFW 초기화
    if (!glfwInit()) {
        std::cerr << "GLFW 초기화 실패" << std::endl;
        return -1;
    }

    // 윈도우 생성 및 OpenGL 컨텍스트 생성
    GLFWwindow* window = glfwCreateWindow(800, 600, "Google Dino Run Copy Game", NULL, NULL);
    if (!window) {
        std::cerr << "윈도우 생성 실패" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 윈도우를 현재 컨텍스트로 지정
    glfwMakeContextCurrent(window);

    // OpenGL 초기화
    glClearColor(0.0f, 0.12f, 0.39f, 1.0f); // 하늘색 배경 설정 (R:0, G:30, B:100)

    // 게임 객체 생성
    int screenHeight = 600;
    int floorY = screenHeight - 100;
    Player player(100, floorY - 50, 50); // Player positioned on top of the floor
    Floor floor(floorY, 800); // Floor y-coordinate

    // EnemyBlock 배열
    EnemyBlock enemyBlocks[] = {
        EnemyBlock(150, floorY - 100, 50, 100),   // Low block
        EnemyBlock(220, floorY - 100, 50, 100),   // Low block
        EnemyBlock(290, floorY - 300, 50, 300),   // High block
        EnemyBlock(360, floorY - 300, 50, 300)    // High block
    };
    int numEnemyBlocks = sizeof(enemyBlocks) / sizeof(enemyBlocks[0]);

    // 창이 열려 있는 동안 반복
    while (!glfwWindowShouldClose(window)) {
        // 화면 지우기
        glClear(GL_COLOR_BUFFER_BIT);

        // 이벤트 처리
        glfwPollEvents();

        // 좌표계 설정
        coordinate(0, 800, 0, 600);

        // 객체 렌더링
        player.Render();
        floor.Render();
        for (int i = 0; i < numEnemyBlocks; ++i) {
            enemyBlocks[i].Render();
        }

        // 충돌 감지
        for (int i = 0; i < numEnemyBlocks; ++i) {
            if (player.CheckCollision(enemyBlocks[i])) {
                player.OnCollisionEnter(enemyBlocks[i]);
                enemyBlocks[i].OnCollisionEnter(player);
            }
        }

        // 렌더링 버퍼 교체
        glfwSwapBuffers(window);
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
