#include "pch.h"
#include "Texture.h"
#include "UnitData.h"
#include "UnitObject.h"
#include "SceneManager.h"
#include "DamageFloat.h"
#include "HealthBar.h"

void UnitObject::SetUnitData(UnitData* _data)
{
	m_unitData = _data;
	m_currentHp = m_unitData->GetMaxHp();
	for (int i = 0; i < 4; ++i) {
		CardData* card = m_unitData->GetCardRandom();
		m_handCards.push_back(card);
	}

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	// 헬스바 사이즈 전반적으로 확대 (폭 100%, 높이 18)
	float barW = size.x * 1.0f;
	float barH = 18.f;

	// 유닛보다 조금 더 아래로 내리기 (기존 +6 에서 +12로)
	float barY = pos.y + size.y * 0.5f + 12.f;

	m_healthBar = new HealthBar(barW, barH);
	m_healthBar->SetPos({ pos.x, barY });
	m_healthBar->SetSize({ barW, barH });
	m_healthBar->SetValue(m_currentHp, m_unitData->GetMaxHp());
}

void UnitObject::Damage(int dmg)
{
	m_currentHp -= dmg;
	if (m_currentHp < 0)
		m_currentHp = 0;

	// 체력바 값 갱신 (UnitObject가 보관한 포인터에 직접 세팅)
	if (m_healthBar)
		m_healthBar->SetValue(m_currentHp, m_unitData ? m_unitData->GetMaxHp() : 0);

	// 데미지 플로팅 생성
	if (auto scene = GET_SINGLE(SceneManager)->GetCurScene())
	{
		Vec2 pos = GetPos();
		Vec2 size = GetSize();

		// 유닛 상단 살짝 위에서 시작
		Vec2 startPos{ pos.x, pos.y - size.y * 0.6f };

		auto* df = new DamageFloat(std::format(L"-{}", dmg), RGB(255, 60, 60), 1.5f);
		df->SetPos(startPos);
		df->SetSize({ 120.f, 40.f }); // 텍스트 박스 크기
		scene->AddObject(df, Layer::CARD);
	}
}


void UnitObject::Render(HDC _hdc)
{
	m_healthBar->Render(_hdc);
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	if (m_isSelect)
	{
		GDISelector penSel(_hdc, PenType::GREEN);
		GDISelector brushSel(_hdc, BrushType::HOLLOW);
		RECT_RENDER(_hdc, pos.x, pos.y, size.x * 1.05f, size.y * 1.05f);
	}

	Texture* tex = m_unitData->GetTexture();
	LONG width = tex->GetWidth();
	LONG height = tex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, (int)size.x
		, (int)size.y
		, tex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));

	// HP 텍스트는 HealthBar에서 출력하므로 여기서는 제거
	// (필요 시 체력바 위치만 이동에 맞춰 동기화)
}
