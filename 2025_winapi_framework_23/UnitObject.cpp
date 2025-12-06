#include "pch.h"
#include "Texture.h"
#include "UnitData.h"
#include "UnitObject.h"
#include "SceneManager.h"
#include "DamageFloat.h"
#include "UnitStatData.h"
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

	m_statData = new UnitStatData(
		m_unitData->GetAtk(),
		m_unitData->GetDef(),
		m_unitData->GetSpeed()
	);
}
void UnitObject::SetBuffStat(StatType _type, int _value)
{
	m_statData->UpgradeStat(_type, _value);
}
void UnitObject::UseCard(int index) {
	m_handCards.push_back(m_unitData->GetCardRandom());
	m_unitData->UseCard(index);
}

void UnitObject::Damage(int dmg, ElementType _type, bool _isPowerup)
{
	int Dmg = dmg - (m_statData->GetStat(StatType::Defense) * 0.4f);

	if (IsStrongAgainst(_type))
	{
		Dmg *= 2;
	}
	else if (IsWeakAgainst(_type))
	{
		Dmg *= 0.5f;
	}
	if (_isPowerup)
	{
		Dmg *= 1.5f;
	}
	m_currentHp -= Dmg;
	if (m_currentHp < 0)
		m_currentHp = 0;

	// 체력바 값 갱신 (UnitObject가 보관한 포인터에 직접 세팅)
	if (m_healthBar)
		m_healthBar->SetValue(m_currentHp, m_unitData ? m_unitData->GetMaxHp() : 0);

	// 데미지 플로팅 생성
	if (auto scene = GET_SINGLE(SceneManager)->GetCurScene())
	{
		Vec2 pos = GetPos();
		auto* df = new DamageFloat(std::format(L"-{}", Dmg), RGB(255, 60, 60), 2.f);
		df->SetPos({ pos.x,pos.y - 40 });
		df->SetSize({ 120.f, 40.f }); // 텍스트 박스 크기
		scene->AddObject(df, Layer::CARD);
	}
}

void UnitObject::Heal(int heal)
{
	m_currentHp += heal;
	if (m_currentHp > m_unitData->GetMaxHp())
		m_currentHp = m_unitData->GetMaxHp();
	// 체력바 값 갱신 (UnitObject가 보관한 포인터에 직접 세팅)
	if (m_healthBar)
		m_healthBar->SetValue(m_currentHp, m_unitData ? m_unitData->GetMaxHp() : 0);
	// 힐 플로팅 생성
	if (auto scene = GET_SINGLE(SceneManager)->GetCurScene())
	{
		Vec2 pos = GetPos();
		auto* df = new DamageFloat(std::format(L"+{}", heal), RGB(60, 255, 60), 2.f);
		df->SetPos({ pos.x,pos.y - 40 });
		df->SetSize({ 120.f, 40.f }); // 텍스트 박스 크기
		scene->AddObject(df, Layer::CARD);
	}
}

int UnitObject::GetStat(StatType _type) const
{
	return m_statData->GetStat(_type);
}
bool UnitObject::IsStrongAgainst(ElementType attacker) const
{
	ElementType defender = m_unitData->GetElementType();
	if ((attacker == ElementType::Fire && defender == ElementType::Ice) ||
		(attacker == ElementType::Water && defender == ElementType::Fire) ||
		(attacker == ElementType::Ice && defender == ElementType::Grace) ||
		(attacker == ElementType::Grace && defender == ElementType::Water))
	{
		return true;
	}
	return false;
}
bool UnitObject::IsWeakAgainst(ElementType attacker) const
{
	ElementType defender = m_unitData->GetElementType();
	if ((defender == ElementType::Fire && attacker == ElementType::Ice) ||
		(defender == ElementType::Water && attacker == ElementType::Fire) ||
		(defender == ElementType::Ice && attacker == ElementType::Grace) ||
		(defender == ElementType::Grace && attacker == ElementType::Water))
	{
		return true;
	}
	return false;
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

	// 체력바 위치/사이즈 동기화 (유닛 하단 조금 아래, 확대된 설정과 동일)
	if (m_healthBar)
	{
		float barW = size.x * 1.0f;
		float barH = 18.f;
		float barY = pos.y + size.y * 0.5f + 12.f;
		m_healthBar->SetPos({ pos.x, barY });
		m_healthBar->SetSize({ barW, barH });

		// 이름 텍스트(체력바 왼쪽에 출력)
		if (m_unitData)
		{
			const std::wstring& name = m_unitData->GetName();

			// 체력바 중심/크기 기반으로 좌측에 이름 영역 구성
			float nameBoxW = std::max(100.f, barW * 0.5f); // 최소 폭 확보
			float nameBoxH = barH;

			RECT nameRc{
				(LONG)(pos.x - barW * 0.5f - 8.f - nameBoxW), // 바 왼쪽보다 약간 더 왼쪽으로
				(LONG)(barY - nameBoxH * 0.5f),
				(LONG)(pos.x - barW * 0.5f - 8.f),             // 바 왼쪽 바로 옆
				(LONG)(barY + nameBoxH * 0.6f)
			};

			int oldBk = ::SetBkMode(_hdc, TRANSPARENT);
			COLORREF oldColor = ::SetTextColor(_hdc, RGB(255, 255, 255));
			{
				GDISelector fontSel(_hdc, FontType::BOLD_UI);


				// 본문
				::SetTextColor(_hdc, RGB(0, 0, 0));
				::DrawTextW(_hdc, name.c_str(), (int)name.length(), &nameRc, DT_RIGHT | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
			}
			::SetTextColor(_hdc, oldColor);
			::SetBkMode(_hdc, oldBk);
		}
	}
}
