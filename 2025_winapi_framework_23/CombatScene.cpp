#include "pch.h"
#include "CardObject.h"
#include "ActionData.h"
#include "CardData.h"
#include "UnitObject.h"
#include "CombatScene.h"

void CombatScene::Init()
{
	for (int i = 0; i < 4; ++i)
	{
		CardObject* card = new CardObject();
		AddObject(card, Layer::CARD);
		card->SetPos(Vec2(100 + i * 120, 300));
		card->SetSize(Vec2(100, 150));
	}
}

void CombatScene::UseCard(UnitType _targetType, int index)
{
	UnitObject* ownerObj = ReturnTypeOfObj(m_currentTurn);
	UnitObject* targetObj = ReturnTypeOfObj(_targetType);
	CardObject* card = m_vecCards[index];
	ActionData* data = new ActionData(ownerObj, targetObj, card, m_currentTurn);
	if (m_currentTurn == UnitType::ENEMY) {
		TurnEnd();
	}
	else {
		m_actionStack.push(data);
		if (m_currentTurn == UnitType::PLAYER1) {
			m_currentTurn = UnitType::PLAYER2;
		}
		else if (m_currentTurn == UnitType::PLAYER2) {
			m_currentTurn = UnitType::ENEMY;
		}
	}
}
UnitObject* CombatScene::ReturnTypeOfObj(UnitType _type) {
	UnitObject* targetData = nullptr;
	switch (_type) {
	case UnitType::PLAYER1: {
		targetData = m_p1Obj;
		break;
	}
	case UnitType::PLAYER2: {
		targetData = m_p2Obj;
		break;
	}
	case UnitType::ENEMY: {
		targetData = m_enemyObj;
		break;
	}
	}
	return targetData;
}


void CombatScene::CancelAction()
{
	if (m_actionStack.empty())
		return;
	ActionData* action = m_actionStack.top();
	m_actionStack.pop();


	m_currentTurn = action->GetTurnType();
}

void CombatScene::TurnEnd()
{
	while (m_actionStack.empty() == false)
	{
		ActionData* action = m_actionStack.top();
		m_actionStack.pop();

		CardData* cardData = action->GetCardObject()->GetCardData();
		CardEffectType effectType = cardData->GetCardEffect();
		switch (effectType)
		{
		case CardEffectType::Damage:
			action->GetTargetUnit()->Damage(cardData->GetEffectValue());
			break;
		}
	}
	m_currentTurn = UnitType::PLAYER1;
}
