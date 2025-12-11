#include "pch.h"
#include "BattleDescription.h"
#include "ActionData.h"
#include "GDISelector.h"

void BattleDescription::SetText(ActionData* _actionData)
{
	if (!_actionData) {
		m_text = L"";
		return;
	}
	wstring ownerName = _actionData->GetOwnerUnit()->GetUnitData()->GetName();
	wstring targetName = _actionData->GetTargetUnit()->GetUnitData()->GetName();
	wstring cardName = _actionData->GetCardObject()->GetName();
	m_text = ownerName + L"(이)가 " + targetName + L"에게 " + cardName + L"을(를) 사용합니다!";
}

void BattleDescription::Render(HDC _hdc)
{

	// Object에서 위치/사이즈 가져와 사용
	const Vec2 pos = GetPos();   // 중앙 좌표
	const Vec2 size = GetSize();  // 배경 박스 크기

	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);

	// 텍스트 영역(중앙 정렬). Define의 중앙기준을 RECT로 변환
	RECT rc{
		(LONG)(pos.x - size.x * 0.5f),
		(LONG)(pos.y - size.y * 0.5f),
		(LONG)(pos.x + size.x * 0.5f),
		(LONG)(pos.y + size.y * 0.5f)
	};
	if (m_text.empty()) return;

	// 폰트/텍스트(검정)
	GDISelector fontSel(_hdc, FontType::PIXEL_BIG);
	int oldBk = ::SetBkMode(_hdc, TRANSPARENT);
	COLORREF oldColor = ::SetTextColor(_hdc, RGB(0, 0, 0));
	::DrawTextW(_hdc, m_text.c_str(), (int)m_text.length(), &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	::SetTextColor(_hdc, oldColor);
	::SetBkMode(_hdc, oldBk);
}

