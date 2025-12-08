#include "pch.h"
#include "DamageFloat.h"
#include "GDISelector.h"
#include "ResourceManager.h"

void DamageFloat::Update()
{
    // 시간 경과
    m_elapsed += fDT;
    if (m_elapsed >= m_lifeTime)
    {
        SetActive(false);
        return;
    }

    // 위치 업데이트 (감속)
    Vec2 pos = GetPos();
    pos.x += m_vel.x * fDT;
    pos.y += m_vel.y * fDT;
    SetPos(pos);

    // 천천히 속도 줄이기
    m_vel.y *= 0.92f;
}

void DamageFloat::Render(HDC _hdc)
{
    if (!IsActive()) return;

    // 투명 배경 + UI 폰트 선택
    GDISelector fontSel(_hdc, FontType::PIXEL_NORMAL);

    // 페이드(명도) 계산
    float t = m_elapsed / m_lifeTime; // 0 -> 1
    float intensity = std::clamp(1.f - t, 0.f, 1.f); // 1 -> 0
    BYTE r = static_cast<BYTE>(GetRValue(m_color) * intensity);
    BYTE g = static_cast<BYTE>(GetGValue(m_color) * intensity);
    BYTE b = static_cast<BYTE>(GetBValue(m_color) * intensity);

    Vec2 pos = GetPos();

    // 텍스트 영역(가운데 정렬)
    RECT rc{
        (LONG)(pos.x - 60),
        (LONG)(pos.y - 30),
        (LONG)(pos.x + 60),
        (LONG)(pos.y + 10)
    };
    {
        HPEN hPen = ::CreatePen(PS_SOLID, 1, RGB(r, g, b));
        HBRUSH hBrush = (HBRUSH)::GetStockObject(HOLLOW_BRUSH); // 내부 비우기 (채우고 싶으면 CreateSolidBrush 사용)
        HPEN oldPen = (HPEN)::SelectObject(_hdc, hPen);
        HBRUSH oldBrush = (HBRUSH)::SelectObject(_hdc, hBrush);
        ::Rectangle(_hdc, rc.left, rc.top, rc.right, rc.bottom);
        ::SelectObject(_hdc, oldPen);
        ::SelectObject(_hdc, oldBrush);
        ::DeleteObject(hPen);
        // (HOLLOW_BRUSH 는 시스템 브러시라 Delete 필요 없음)
    }
    // 그림자
    int oldBk = ::SetBkMode(_hdc, TRANSPARENT);
    COLORREF oldColor = ::SetTextColor(_hdc, RGB(0, 0, 0));

    RECT shadowRc = rc;
    ::OffsetRect(&shadowRc, 1, 1);
    ::DrawTextW(_hdc, m_text.c_str(), (int)m_text.length(), &shadowRc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    // 본문
    ::SetTextColor(_hdc, RGB(r, g, b));
    ::DrawTextW(_hdc, m_text.c_str(), (int)m_text.length(), &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

    ::SetTextColor(_hdc, oldColor);
    ::SetBkMode(_hdc, oldBk);
}