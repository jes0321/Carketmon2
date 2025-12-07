#pragma once
#include "pch.h"
class UnitObject;
class ActionData;
class CardData;
class UnitData;
class BattleDescription;

class BattleScene;
class CombatManager
{
	DECLARE_SINGLE(CombatManager);
public:
    void Init();
    void Update();
    void Render(HDC _hdc);

public:
	void SetUnitData(UnitType _type, UnitData* _data);
    void SetEnemy(UnitData* _data);
    void EndTurn();
    void AddAction(UnitType _target, int index);
    void CancelAction(UnitType _ownerType);
	void HealUnit(UnitType _type);

    UnitObject* GetUnit(UnitType type);
    vector<CardData*> GetHandCard();
	int GetLifeCount() const { return m_lifeCount; }

private:
	void EnemyTurn();
	void EndActions(BattleScene* battleScene);

    void DamageUnit(ActionData* action);
	void HealUnit(ActionData* action);
	void StatControl(ActionData* action);
	void BuffTarget(ActionData* action);
	void SetFocus(bool _isFocus, ActionData* action = nullptr);
private:
	int m_lifeCount = 3;
	bool m_isFocus = false;
	UnitObject* m_focusUnit;
	UnitType m_currentTurn;
	bool m_isWait = false;
	float m_delayTime = 3.f;
	float m_timer = 0;
	vector<ActionData*> m_actionList;
	vector<UnitObject*> m_units;
	vector<UnitObject*> m_deadUnits;
};

