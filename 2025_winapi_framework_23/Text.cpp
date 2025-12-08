#include "pch.h"
#include "Text.h"

Text::Text(std::wstring _text)
{
	m_text = _text;
}

Text::~Text()
{

}

void Text::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	RECT rc;

	rc.left = static_cast<LONG>(pos.x - size.x / 2);
	rc.top = static_cast<LONG>(pos.y - size.y / 2);
	rc.right = static_cast<LONG>(pos.x + size.x / 2);
	rc.bottom = static_cast<LONG>(pos.y + size.y / 2);

	::DrawTextW(_hdc, m_text.c_str(), -1, &rc, DT_WORDBREAK | DT_CENTER | DT_VCENTER);
}
