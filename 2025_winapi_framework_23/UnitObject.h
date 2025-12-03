#pragma once
#include "Object.h"
#include "UnitData.h"
class HealthBar;
class CardData;
class UnitStatData;
class UnitObject : public Object
{
public:
	void Render(HDC _hdc) override;
public:
	void SetUnitData(UnitData* _data);
	void UseCard(int index) { m_unitData->UseCard(index); }
	void Damage(int dmg);
	void SetSelect(bool isSelect) { m_isSelect = isSelect; }
	UnitData* GetUnitData() const { return m_unitData; }
	CardData* GetCardRandom() const { return m_unitData->GetCardRandom(); }
	CardData* GetCardInHand(int index) const { return m_handCards[index]; }
	vector<CardData*> GetHandCards() const { return m_handCards; }

	int GetCurrentHp() const { return m_currentHp; }
	int GetStat(StatType _type) const;
private :
	bool m_isSelect = false;
	vector<CardData*> m_handCards;
	int m_currentHp = 0;
	UnitData* m_unitData = nullptr;
	UnitStatData* m_statData = nullptr;

	// 체력바 포인터를 들고 있어 Damage 등에서 SetValue를 호출
	HealthBar* m_healthBar = nullptr;
};
