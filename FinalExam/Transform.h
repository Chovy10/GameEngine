#ifndef TRANSfORM_H
#define TRANSfORM_H

class Transform {
public:
    Transform(float x, float y) : m_X(x), m_Y(y), m_Rotation(0), m_Scale(1) {}

    // 이동 함수: 미터 단위로 이동
    void Translate(float dx, float dy) {
        m_X += dx;
        m_Y += dy;
    }

    // 회전 함수: 각도 단위로 회전 (시계 방향)
    void Rotate(float degrees) {
        m_Rotation += degrees;
    }

    // 배율 조정 함수
    void Scale(float factor) {
        m_Scale *= factor;
    }

    // 위치 Getter
    float GetPositionX() const { return m_X; }
    float GetPositionY() const { return m_Y; }

    // 장애물 재활용 함수: 장애물을 화면 우측 끝에서 다시 시작 위치로 이동
    void Recycle(float screenWidth) {
        // 화면 우측 끝으로 이동
        m_X = screenWidth;
    }

private:
    float m_X;        // x 좌표
    float m_Y;        // y 좌표
    float m_Rotation; // 회전 각도
    float m_Scale;    // 크기 배율
};

#endif

