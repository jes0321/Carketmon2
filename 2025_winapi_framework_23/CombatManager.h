#pragma once
#include "pch.h"
class UnitObject;
class ActionData;
class CardData;
class CombatManager
{
	DECLARE_SINGLE(CombatManager);
public:
	void Init();
	void Render(HDC _hdc);
public:
	void EndTurn();
	void AddAction(UnitType _target,int index);
	void CancelAction(UnitType _ownerType);
	UnitObject* GetUnit(UnitType type);
	vector<CardData*> GetHandCard();
private :
	void DamageUnit(ActionData* action);
private:
	UnitType m_currentTurn;
	vector<ActionData*> m_actionList;
	vector<UnitObject*> m_units;
};

