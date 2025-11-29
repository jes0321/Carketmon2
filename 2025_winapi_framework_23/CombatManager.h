#pragma once
#include "pch.h"
class UnitObject;
class ActionData;
class CombatManager
{
	DECLARE_SINGLE(CombatManager);
public:
	void AddAction(UnitType _target,int index);
	void CancelAction(UnitType _ownerType);
	UnitObject* GetUnit(UnitType type);
private:
	UnitType m_currentTurn;
	vector<ActionData*> m_actionQueue;
	vector<UnitObject*> m_units;
};

