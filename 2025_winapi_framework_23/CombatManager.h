#pragma once
#include "pch.h"
class UnitObject;
class ActionData;
class CardData;
class UnitData;
class BattleDescription;

class CombatManager
{
	DECLARE_SINGLE(CombatManager);
public:
    void Init();
    void Update();
    void Render(HDC _hdc);

    void SetEnemy(UnitData* _data);
    void EndTurn();
    void AddAction(UnitType _target, int index);
    void CancelAction(UnitType _ownerType);

    UnitObject* GetUnit(UnitType type);
    vector<CardData*> GetHandCard();


private:
    void DamageUnit(ActionData* action);
	void HealUnit(ActionData* action);

private:
	UnitType m_currentTurn;
	bool m_isWait = false;
	float m_delayTime = 3.f;
	float m_timer = 0;
	vector<ActionData*> m_actionList;
	vector<UnitObject*> m_units;
};

