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
	void SetBuffStat(StatType _type, int _value);
	void UseCard(int index);
	void Damage(int dmg,ElementType _type, bool _isPowerup);
	void Heal(int heal);
	void SetSelect(bool isSelect) { m_isSelect = isSelect; }
	void SetPowerup(bool isPowerup) { m_isPowerup = isPowerup; }
	UnitStatData* GetStatData() const { return m_statData; }
	UnitData* GetUnitData() const { return m_unitData; }
	CardData* GetCardRandom() const { return m_unitData->GetCardRandom(); }
	CardData* GetCardInHand(int index) const { return m_handCards[index]; }
	vector<CardData*> GetHandCards() const { return m_handCards; }

	bool IsPowerup() const { return m_isPowerup; }
	int GetCurrentHp() const { return m_currentHp; }
	int GetStat(StatType _type) const;
private:
	bool IsStrongAgainst(ElementType attacker) const;
	bool IsWeakAgainst(ElementType attacker) const;
private :
	bool m_isPowerup = false;
	bool m_isSelect = false;
	vector<CardData*> m_handCards;
	int m_currentHp = 0;
	UnitData* m_unitData = nullptr;
	UnitStatData* m_statData = nullptr;

	// 체력바 포인터를 들고 있어 Damage 등에서 SetValue를 호출
	HealthBar* m_healthBar = nullptr;
};
