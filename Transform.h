#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <cmath>
#include <iostream> // for debugging

class Transform {
public:
    Transform(float x, float y, float speed)
        : m_X(x), m_Y(y), m_Speed(speed), m_Width(50), m_Height(100) {}

    // ���� ���� �̵� �Լ�
    void Translate(float dx, float dy) {
        m_X += dx;
        m_Y += dy;
    }

    // X ��ǥ Getter
    float GetPositionX() const { return m_X; }

    // Y ��ǥ Getter
    float GetPositionY() const { return m_Y; }

    // ��ֹ� ��Ȱ�� �Լ�
    void Recycle(float screenWidth) {
        m_X = screenWidth; // ȭ�� ������ ������ �̵�
    }

private:
    float m_X;       // x ��ǥ
    float m_Y;       // y ��ǥ
    float m_Speed;   // �̵� �ӵ�
    float m_Width;   // ��ֹ� �ʺ�
    float m_Height;  // ��ֹ� ����
};

#endif

