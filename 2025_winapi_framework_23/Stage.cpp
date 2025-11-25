#include "pch.h"
#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Update()
{
}

void Stage::Render(HDC _hdc)
{
	COLORREF color = isSeleted ? RGB(100, 100, 100) : RGB(255, 255, 255);
	HBRUSH hbrush = ::CreateSolidBrush(color);
	HBRUSH holdbrush = (HBRUSH)::SelectObject(_hdc, hbrush);

	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	::SelectObject(_hdc, holdbrush);
	::DeleteObject(hbrush);
}
