#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

void coordinate(int left, int right, int bottom, int top) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, -1, 1); // 2D 좌표 시스템 설정
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

    virtual void Update(float deltaTime) {
        // Define this function in derived classes if needed
    }

    void SetX(int newX) {
        x = newX;
    }

    int GetX() const {
        return x;
    }

    int GetY() const {
        return y;
    }

    int GetWidth() const {
        return width;
    }

    int GetHeight() const {
        return height;
    }

    void SetY(int newY) {
        y = newY;
    }
};

class Player : public Object {
private:
    float velocityY; // 속도
    bool isJumping;

public:
    Player(int x, int y, int size)
        : Object(x, y, size, size), velocityY(0), isJumping(false) {}

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

    void Update(float deltaTime) override {
        // 중력 적용
        float gravity = 1000.0f; // 중력 가속도 (1000px/s^2)
        velocityY += gravity * deltaTime;

        // 위치 업데이트
        y += static_cast<int>(velocityY * deltaTime);

        // 땅 아래로는 못 가게 설정
        if (y + height >= 500) {
            y = 500 - height;
            velocityY = 0;
            isJumping = false;
        }
    }

    void Jump() {
        if (!isJumping) {
            velocityY = -500.0f; // 점프 초기 속도 (500px/s)
            isJumping = true;
        }
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
private:
    float speed; // 속도 변수 추가

public:
    EnemyBlock(int x, int y, int width, int height, float speed)
        : Object(x, y, width, height), speed(speed) {}

    void Render() const override {
        glColor3f(0.0f, 1.0f, 0.0f); // Green color
        glBegin(GL_QUADS);
        glVertex2i(x, y);
        glVertex2i(x + width, y);
        glVertex2i(x + width, y + height);
        glVertex2i(x, y + height);
        glEnd();
    }

    void Update(float deltaTime) override {
        x -= static_cast<int>(speed * deltaTime); // 좌측으로 이동

        // 화면을 벗어나면 오른쪽 끝에서 다시 나타나도록 설정
        if (x + width < 0) {
            x = 800; // 오른쪽 끝에서 나타나도록 설정
        }
    }
};

int PhysicsAABB(Object& A, Object& B) {
    if (A.CheckCollision(B)) {
        return 1; // 충돌 발생
    }
    return 0; // 충돌 없음
}

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
        EnemyBlock(800, floorY - 100, 50, 100, 100.0f),   // Low block
        EnemyBlock(1000, floorY - 100, 50, 100, 100.0f),  // Low block
        EnemyBlock(1200, floorY - 300, 50, 300, 100.0f)   // High block
    };
    int numEnemyBlocks = sizeof(enemyBlocks) / sizeof(enemyBlocks[0]);

    // 이전 프레임 시간 저장 변수
    double lastTime = glfwGetTime();

    // 창이 열려 있는 동안 반복
    while (!glfwWindowShouldClose(window)) {
        // 현재 시간 가져오기
        double currentTime = glfwGetTime();
        float deltaTime = static_cast<float>(currentTime - lastTime);
        lastTime = currentTime;

        // 화면 지우기
        glClear(GL_COLOR_BUFFER_BIT);

        // 이벤트 처리
        glfwPollEvents();

        // 점프 키 입력 처리
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            player.Jump();
        }

        // 좌표계 설정
        coordinate(0, 800, screenHeight, 0); // bottom을 screenHeight으로 설정하여 Y축 반전

        // 객체 렌더링 및 업데이트
        player.Render();
        player.Update(deltaTime);
        floor.Render();
        for (int i = 0; i < numEnemyBlocks; ++i) {
            enemyBlocks[i].Render();
            enemyBlocks[i].Update(deltaTime); // 이동 업데이트
        }

        // 충돌 감지
        for (int i = 0; i < numEnemyBlocks; ++i) {
            if (PhysicsAABB(player, enemyBlocks[i])) {
                std::cout << "게임 종료!" << std::endl;
                glfwSetWindowShouldClose(window, GLFW_TRUE);
            }
        }

        // 렌더링 버퍼 교체
        glfwSwapBuffers(window);
    }

    // GLFW 종료
    glfwTerminate();
    return 0;
}
