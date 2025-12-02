#pragma once
#include "Object.h"
#undef max

class HealthBar : public Object
{
public:
    HealthBar(float width = 100.f, float height = 10.f)
        : m_barWidth(width), m_barHeight(height) {}

    // 유닛 체력 고정 값 세팅 (유닛 이동 없음 가정)
    void SetValue(int cur, int max)
    {
        m_curHp = std::max(0, cur);
        m_maxHp = std::max(0, max);
        if (m_curHp > m_maxHp) m_curHp = m_maxHp;
    }

    void Render(HDC _hdc) override;

private:
    float m_barWidth = 100.f;
    float m_barHeight = 10.f;

    int m_curHp = 0;
    int m_maxHp = 0;
};

