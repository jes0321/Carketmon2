#include "pch.h"
#include "Button.h"
#include "ResourceManager.h"

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
	}

	HBRUSH hbrush = ::CreateSolidBrush(color);
	HBRUSH holdbrush = (HBRUSH)::SelectObject(_hdc, hbrush);

	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	::SelectObject(_hdc, holdbrush);
	::DeleteObject(hbrush);

	if (m_texture == nullptr) return;

	LONG width = m_texture->GetWidth();
	LONG height = m_texture->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, (int)size.x
		, (int)size.y
		, m_texture->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}

void Button::Update()
{

}
