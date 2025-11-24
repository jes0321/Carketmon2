#pragma once
#include "Object.h"
class UnitData;
class UnitObject : public Object
{
public:
	void SetUnitData(UnitData* _data) { m_unitData = _data; }
	UnitData* GetUnitData() const { return m_unitData; }
	CardData* GetCardRandom() const { return m_unitData->GetCardRandom(); }
	void Render(HDC _hdc) override;
private :
	UnitData* m_unitData;
};

