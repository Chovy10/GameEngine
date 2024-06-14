#ifndef TRANSfORM_H
#define TRANSfORM_H

class Transform {
public:
    Transform(float x, float y) : m_X(x), m_Y(y), m_Rotation(0), m_Scale(1) {}

    // �̵� �Լ�: ���� ������ �̵�
    void Translate(float dx, float dy) {
        m_X += dx;
        m_Y += dy;
    }

    // ȸ�� �Լ�: ���� ������ ȸ�� (�ð� ����)
    void Rotate(float degrees) {
        m_Rotation += degrees;
    }

    // ���� ���� �Լ�
    void Scale(float factor) {
        m_Scale *= factor;
    }

    // ��ġ Getter
    float GetPositionX() const { return m_X; }
    float GetPositionY() const { return m_Y; }

    // ��ֹ� ��Ȱ�� �Լ�: ��ֹ��� ȭ�� ���� ������ �ٽ� ���� ��ġ�� �̵�
    void Recycle(float screenWidth) {
        // ȭ�� ���� ������ �̵�
        m_X = screenWidth;
    }

private:
    float m_X;        // x ��ǥ
    float m_Y;        // y ��ǥ
    float m_Rotation; // ȸ�� ����
    float m_Scale;    // ũ�� ����
};

#endif

