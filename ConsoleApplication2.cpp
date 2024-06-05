#include <SFML/Graphics.hpp>
#include <cmath>

// 픽셀을 미터로 변환하는 상수
const float PIXELS_TO_METERS = 100.0f;

int main()
{
    // 창 생성
    sf::RenderWindow window(sf::VideoMode(800, 600), "Gravity and Movement");

    // 네모 물체 생성
    sf::RectangleShape rectangle(sf::Vector2f(100, 100)); // 1x1 미터로 설정
    rectangle.setFillColor(sf::Color::Green);
    rectangle.setPosition(400, 0); // 시작 위치 (픽셀 단위)

    // 바닥 생성
    sf::RectangleShape ground(sf::Vector2f(800, 50)); // 8x0.5 미터로 설정
    ground.setFillColor(sf::Color::Blue);
    ground.setPosition(0, window.getSize().y - ground.getSize().y); // 창의 아래에 위치

    // 초기 중력가속도 (미터/초^2)
    float gravityInitial = 9.81f;
    // 중력의 변화율 (미터/초^3)
    float gravityRate = -0.1f;

    // 초기 속도 설정 (픽셀/초)
    sf::Vector2f velocity(0.0f, 0.0f);
    // 이동 속도 (픽셀/초)
    float moveSpeed = 200.0f;

    // 게임 루프
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // 이벤트 처리
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // 키보드 입력 처리
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocity.x = -moveSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocity.x = moveSpeed;
        }
        else
        {
            velocity.x = 0.0f;
        }

        // 중력 적용
        float gravity = gravityInitial + gravityRate * clock.getElapsedTime().asSeconds();
        velocity.y += gravity * dt * PIXELS_TO_METERS; // 중력 적용

        // 윗키를 누르면 바닥에 닿았을 때만 물체가 점프하도록 함
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rectangle.getPosition().y + rectangle.getSize().y >= ground.getPosition().y)
        {
            velocity.y = -sqrtf(2.0f * gravity * PIXELS_TO_METERS); // 제곱근을 이용한 초기 속도 계산
        }

        // 바닥에 닿으면 물체의 y 속도를 0으로 설정하여 점프할 수 있게 함
        if (rectangle.getPosition().y + rectangle.getSize().y >= ground.getPosition().y)
        {
            // 윗키를 눌렀을 때 물체가 점프하도록 함
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                velocity.y = -sqrtf(200.0f * gravity * PIXELS_TO_METERS); // 제곱근을 이용한 초기 속도 계산
            }
            else
            {
                velocity.y = 0.0f;
                // 바닥에 닿으면 y 위치를 조정하여 물체가 바닥 위에 위치하도록 함
                rectangle.setPosition(rectangle.getPosition().x, ground.getPosition().y - rectangle.getSize().y);
            }
        }

        // 물체 이동
        rectangle.move(velocity * dt); // 시간 단위로 이동 속도를 조정

        // 화면 지우고 그리기
        window.clear();
        window.draw(rectangle);
        window.draw(ground);
        window.display();
    }

    return 0;
}
