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
	COLORREF color;

	if (IsAvailable)
		color = IsSeleted ? RGB(100, 100, 100) : RGB(255, 255, 255);
	else
	{
		color = IsCompelet ? RGB(255, 255, 0) : RGB(255, 0, 255);
	}

	HBRUSH hbrush = ::CreateSolidBrush(color);
	HBRUSH holdbrush = (HBRUSH)::SelectObject(_hdc, hbrush);

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	if (m_nextStages.empty() == false)
	{
		for (int i = 0; i < m_nextStages.size(); i++)
		{
			::MoveToEx(_hdc, pos.x, pos.y, nullptr);

			Vec2 nextPos = m_nextStages[i]->GetPos();
			::LineTo(_hdc, nextPos.x, nextPos.y);
		}
	}

	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	RECT rc;
	rc.left = static_cast<LONG>(pos.x);
	rc.top = static_cast<LONG>(pos.y);
	rc.right = static_cast<LONG>(pos.x + size.x);
	rc.bottom = static_cast<LONG>(pos.y + size.y);

	std::wstring text = std::to_wstring(m_stageNumber);

	::SetTextColor(_hdc, IsSeleted ? RGB(255, 255, 255) : RGB(0, 0, 0));
	::SetBkMode(_hdc, TRANSPARENT);

	::DrawTextW(_hdc, text.c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	::SelectObject(_hdc, holdbrush);
	::DeleteObject(hbrush);
}
