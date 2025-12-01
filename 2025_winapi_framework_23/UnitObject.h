#pragma once
#include "Object.h"
#include "UnitData.h"
class CardData;
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
private :
	bool m_isSelect = false;
	vector<CardData*> m_handCards;
	int m_currentHp;
	UnitData* m_unitData;
};
