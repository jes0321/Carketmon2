#pragma once
#include "Object.h"
#include "UnitData.h"
class HealthBar;
class CardData;
class UnitStatData;
class UnitObject : public Object
{
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	void SetUnitData(UnitData* _data);
	void SetBuffStat(StatType _type, int _value);
	void UseCard(int index);
	void Damage(int dmg,ElementType _type, bool _isPowerup);
	void Heal(int heal,bool _floating=true);
	void SetSelect(bool isSelect) { m_isSelect = isSelect; }
	void SetPowerup(bool isPowerup) { m_isPowerup = isPowerup; }
	void SetSheilded(bool isSheilded) { m_isSheilded = isSheilded; }
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
	bool m_isSheilded = false;
	bool m_isPowerup = false;
	bool m_isSelect = false;
	vector<CardData*> m_handCards;
	int m_currentHp = 0;
	UnitData* m_unitData = nullptr;
	UnitStatData* m_statData = nullptr;

	// 체력바 포인터를 들고 있어 Damage 등에서 SetValue를 호출
	HealthBar* m_healthBar = nullptr;

	// 데미지 시 블링크 상태 (fDT 기반으로 변경)
	bool   m_isBlinking     = false;
	bool   m_isBlinkVisible = true;
	float  m_blinkRemain    = 0.f;   // 남은 전체 블링크 시간(초)
	float  m_blinkAccum     = 0.f;   // 토글 간격 누적(초)
	float  m_blinkInterval  = 0.08f; // 80ms 간격(초)
};
