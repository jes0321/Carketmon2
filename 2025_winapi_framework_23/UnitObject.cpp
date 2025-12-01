#include "pch.h"
#include "Texture.h"
#include "UnitData.h"
#include "UnitObject.h"
#include "SceneManager.h"
#include "DamageFloat.h"
void UnitObject::SetUnitData(UnitData* _data)
{
	m_unitData = _data;
	m_currentHp = m_unitData->GetMaxHp();
	for (int i = 0; i < 4; ++i) {
		CardData* card = m_unitData->GetCardRandom();
		m_handCards.push_back(card);
	}
}

void UnitObject::Damage(int dmg)
{
	m_currentHp -= dmg; 
	if (m_currentHp < 0) 
		m_currentHp = 0;
	// 데미지 플로팅 생성
	if (auto scene = GET_SINGLE(SceneManager)->GetCurScene())
	{
		Vec2 pos = GetPos();
		Vec2 size = GetSize();

		// 유닛 상단 살짝 위에서 시작
		Vec2 startPos{ pos.x, pos.y - size.y * 0.6f };

		auto* df = new DamageFloat(std::format(L"-{}", dmg), RGB(255, 60, 60), 0.9f);
		df->SetPos(startPos);
		df->SetSize({ 120.f, 40.f }); // 텍스트 박스 크기
		scene->AddObject(df, Layer::UI);
	}
}


void UnitObject::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	if (m_isSelect)
	{
		// 초록 테두리, 속 빈 브러시로 윤곽선만
		GDISelector penSel(_hdc, PenType::GREEN);
		GDISelector brushSel(_hdc, BrushType::HOLLOW);


		RECT_RENDER(_hdc, pos.x, pos.y, size.x * 1.05, size.y * 1.05);
	}
	Texture* tex = m_unitData->GetTexture();
	LONG width = tex->GetWidth();
	LONG height = tex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, tex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));
	const int curHp = m_currentHp;
	const int maxHp = m_unitData ? m_unitData->GetMaxHp() : 0;
	std::wstring hpText = std::format(L"{} / {}", curHp, maxHp);

	// 유닛 이미지 바로 아래 가운데 정렬
	int left = (int)(pos.x - size.x / 2);
	int right = (int)(pos.x + size.x / 2);
	int top = (int)(pos.y + size.y / 2) + 2;
	int bottom = top + 20;
	RECT rc{ left, top, right, bottom };

	// 가독성을 위한 그림자 + 흰색 텍스트
	int oldBk = ::SetBkMode(_hdc, TRANSPARENT);
	COLORREF oldColor = ::SetTextColor(_hdc, RGB(255, 255, 255));

	RECT shadowRc = rc;
	::OffsetRect(&shadowRc, 1, 1);
	::SetTextColor(_hdc, RGB(0, 0, 0));
	::DrawTextW(_hdc, hpText.c_str(), (int)hpText.length(), &shadowRc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	::SetTextColor(_hdc, RGB(255, 255, 255));
	::DrawTextW(_hdc, hpText.c_str(), (int)hpText.length(), &rc, DT_CENTER | DT_SINGLELINE | DT_VCENTER);

	::SetTextColor(_hdc, oldColor);
	::SetBkMode(_hdc, oldBk);
}
