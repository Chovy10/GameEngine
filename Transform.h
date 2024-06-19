#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <iostream> // for debugging

class Transform {
public:
    Transform(float x, float y, float speed)
        : m_X(x), m_Y(y), m_Speed(speed), m_Width(50), m_Height(100) {}

    // 미터 단위 이동 함수
    void Translate(float dx, float dy) {
        m_X += dx;
        m_Y += dy;
    }

    // X 좌표 Getter
    float GetPositionX() const { return m_X; }

    // Y 좌표 Getter
    float GetPositionY() const { return m_Y; }

    // 장애물 재활용 함수
    void Recycle(float screenWidth) {
        m_X = screenWidth; // 화면 오른쪽 끝으로 이동
    }

private:
    float m_X;       // x 좌표
    float m_Y;       // y 좌표
    float m_Speed;   // 이동 속도
    float m_Width;   // 장애물 너비
    float m_Height;  // 장애물 높이
};

#endif

