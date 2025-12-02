#pragma once
#include "Object.h"

class DamageFloat : public Object
{
public:
    DamageFloat(const std::wstring& text, COLORREF color, float lifeTimeSec = 0.9f)
        : m_text(text), m_color(color), m_lifeTime(lifeTimeSec) {
    }

    void Update() override;
    void Render(HDC _hdc) override;

private:
    std::wstring m_text;
    COLORREF m_color = RGB(255, 0, 0);
    float m_lifeTime = 0.9f;
    float m_elapsed = 0.f;

    // 간단한 부유 애니메이션 파라미터
    Vec2 m_vel{ 0.f, -80.f }; // 위로 떠오름(px/s)
};