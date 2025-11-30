#include "pch.h"
#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Render(HDC _hdc)
{
	COLORREF color = RGB(100, 100, 100);

	switch (m_buttonState)
	{
	case Default:
		color = RGB(100, 100, 100);
		break;
	case Clicked:
		color = RGB(255, 255, 255);
		break;
	case Selected:
		color = RGB(200, 200, 200);
		break;
	default:
		break;
	}

	HBRUSH hbrush = ::CreateSolidBrush(color);
	HBRUSH holdbrush = (HBRUSH)::SelectObject(_hdc, hbrush);

	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	::SelectObject(_hdc, holdbrush);
	::DeleteObject(hbrush);
}

void Button::Update()
{

}
