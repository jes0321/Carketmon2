#pragma once
#include "UnitData.h"
class UnitData;
class UnitManager
{
	DECLARE_SINGLE(UnitManager);
public:
	void Init();
	void Release();
public :
	UnitData* GetUnit(const wstring _unitName);
	UnitData* GetUnitRandom();
private:
	UnitData* RegisterUnit(wstring _name, wstring _texName, int _maxHp, int _atk,int _def,int _spd,ElementType _type, UnitCategory _category);
private:
	std::unordered_map<wstring, UnitData*> m_mapUnits;
};

