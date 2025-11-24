#pragma once
#include "Object.h"
class UnitData;
class UnitObject : public Object
{
public:
	void SetUnitData(UnitData* _data);
	UnitData* GetUnitData() const { return m_unitData; }
	void UseCard(int index) { m_unitData->UseCard(index); }
	CardData* GetCardRandom() const { return m_unitData->GetCardRandom(); }
	void Render(HDC _hdc) override;
private :
	int m_currentHp;
	UnitData* m_unitData;
};

