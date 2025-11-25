#pragma once
#include "Scene.h"
class CardObject;
class UnitObject;
class ActionData;
class CombatScene : public Scene
{
public:
	void Init() override;
public:
	CardObject* GetCardObject(int index) const { return m_vecCards[index]; }
private :
	void UseCard(int index);
	void SetCard(CardObject* cardObj) { m_vecCards.push_back(cardObj); }
	void CancelAction();
	void TurnEnd();
private :
	UnitObject* m_p1Obj;
	UnitObject* m_p2Obj;
	UnitObject* m_enemyObj;
	TurnType m_currentTurn;
	std::stack<ActionData*> m_actionStack;
	vector<CardObject*> m_vecCards;
};

