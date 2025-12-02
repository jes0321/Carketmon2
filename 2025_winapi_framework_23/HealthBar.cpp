#include "pch.h"
#include "HealthBar.h"
#include "GDISelector.h"

void HealthBar::Render(HDC _hdc)
{
	if (!IsActive()) return;

	float ratio = (m_maxHp > 0) ? (float)m_curHp / (float)m_maxHp : 0.f;
	ratio = std::clamp(ratio, 0.f, 1.f);

	Vec2 p = GetPos();
	Vec2 s = GetSize();

	// 배경
	{
		HPEN oldPen = (HPEN)::SelectObject(_hdc, (HPEN)::GetStockObject(NULL_PEN));
		HBRUSH backBrush = ::CreateSolidBrush(RGB(40, 40, 40));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(_hdc, backBrush);
		RECT_RENDER(_hdc, p.x, p.y, s.x, s.y);
		::SelectObject(_hdc, oldBrush);
		::DeleteObject(backBrush);
		::SelectObject(_hdc, oldPen);
	}

	// 채움: 왼쪽 고정(오른쪽부터 줄어들게)
	{
		float fillWidth = std::max(0.f, s.x * ratio);
		BYTE r = (BYTE)(255 * (1.f - ratio));
		BYTE g = (BYTE)(200 * ratio);

		// 전체 바의 왼쪽 가장자리 좌표
		float left = p.x - (s.x * 0.5f);
		// 중앙 기준 렌더러에 맞춰 채움 중심 X 계산
		float fillCenterX = left + (fillWidth * 0.5f);

		HPEN oldPen = (HPEN)::SelectObject(_hdc, (HPEN)::GetStockObject(NULL_PEN));
		HBRUSH fillBrush = ::CreateSolidBrush(RGB(r, g, 60));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(_hdc, fillBrush);
		RECT_RENDER(_hdc, fillCenterX, p.y, fillWidth, s.y);
		::SelectObject(_hdc, oldBrush);
		::DeleteObject(fillBrush);
		::SelectObject(_hdc, oldPen);
	}

	// 테두리
	{
		HPEN borderPen = ::CreatePen(PS_SOLID, 1, RGB(200, 200, 200));
		HPEN oldPen = (HPEN)::SelectObject(_hdc, borderPen);
		HBRUSH oldBrush = (HBRUSH)::SelectObject(_hdc, (HBRUSH)::GetStockObject(HOLLOW_BRUSH));
		RECT_RENDER(_hdc, p.x, p.y, s.x, s.y);
		::SelectObject(_hdc, oldPen);
		::SelectObject(_hdc, oldBrush);
		::DeleteObject(borderPen);
	}

	// 중앙 텍스트(현재/최대) - 살짝 위로 올림 (예: 2px)
	std::wstring hpText = std::format(L"{} / {}", m_curHp, m_maxHp);
	RECT rcText{
		(LONG)(p.x - s.x / 2),
		(LONG)(p.y - s.y / 2 - 2),  // 위로 조금 올림
		(LONG)(p.x + s.x / 2),
		(LONG)(p.y + s.y / 2 - 2)   // 위로 조금 올림
	};

	int oldBk = ::SetBkMode(_hdc, TRANSPARENT);
	COLORREF oldColor = ::SetTextColor(_hdc, RGB(255, 255, 255));
	{
		GDISelector fontSel(_hdc, FontType::UI);

		::SetTextColor(_hdc, RGB(0, 0, 0));
		RECT shadow = rcText; ::OffsetRect(&shadow, 1, 1);
		::DrawTextW(_hdc, hpText.c_str(), (int)hpText.length(), &shadow, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

		::SetTextColor(_hdc, RGB(255, 255, 255));
		::DrawTextW(_hdc, hpText.c_str(), (int)hpText.length(), &rcText, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
	}
	::SetTextColor(_hdc, oldColor);
	::SetBkMode(_hdc, oldBk);
}
