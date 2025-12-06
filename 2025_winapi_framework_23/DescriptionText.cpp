#include "pch.h"
#include "DescriptionText.h"
#include "CardObject.h"

void DescriptionText::Render(HDC _hdc)
{
	if (m_targetCardObj == nullptr)
		return;

	// 카드 이름/설명 가져오기
	const std::wstring name = m_targetCardObj->GetCardName();
	const std::wstring desc = m_targetCardObj->GetCardDescription();

	// 출력 문자열
	const std::wstring lineName = std::format(L"이름 : {}", name);
	const std::wstring lineDesc = std::format(L"{}", desc);

	// 위치/영역 계산
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
	RECT rc = {
		(LONG)(pos.x - size.x / 2),
		(LONG)(pos.y - size.y / 2),
		(LONG)(pos.x + size.x / 2),
		(LONG)(pos.y + size.y / 2)
	};

	// 이름 영역(상단), 설명 영역(아래)
	LONG nameHeight = 28; // 이름 한 줄 높이
	RECT rcName = rc;
	rcName.bottom = rcName.top + nameHeight;

	RECT rcDesc = rc;
	rcDesc.top += nameHeight + 4;

	// 공통 렌더 설정
	int oldBk = ::SetBkMode(_hdc, TRANSPARENT);

	// 이름: TITLE 폰트, 가운데 정렬 한 줄
	{
		GDISelector fontTitle(_hdc, FontType::BOLD_UI);
		// 그림자
		::SetTextColor(_hdc, RGB(0, 0, 0));
		::DrawTextW(_hdc, lineName.c_str(), (int)lineName.size(), &rcName, DT_CENTER | DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX);
	}

	// 설명: UI 폰트, 워드브레이크로 여러 줄
	{
		GDISelector fontUI(_hdc, FontType::BOLD_UI);
		::SetTextColor(_hdc, RGB(0, 0, 0));
		::DrawTextW(_hdc, lineDesc.c_str(), (int)lineDesc.size(), &rcDesc, DT_CENTER | DT_WORDBREAK | DT_NOPREFIX);
	}

	::SetBkMode(_hdc, oldBk);
}