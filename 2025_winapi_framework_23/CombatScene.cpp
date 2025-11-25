#include "pch.h"
#include "CardObject.h"
#include "ActionData.h"
#include "CardData.h"
#include "UnitObject.h"
#include "CombatScene.h"

void CombatScene::Init()
{
	for(int i=0; i < 4; ++i)
	{
		CardObject* card = new CardObject();
		AddObject(card, Layer::CARD);
		card->SetPos(Vec2(100 + i * 120, 300));
		card->SetSize(Vec2(100, 150));
	}
}

void CombatScene::UseCard(int index)
{
	
}

void CombatScene::CancelAction()
{
	if(m_actionStack.empty())
		return;
	ActionData* action = m_actionStack.top();
	m_actionStack.pop();

	
	m_currentTurn = action->GetTurnType();
}

void CombatScene::TurnEnd()
{
	while(m_actionStack.empty() == false)
	{
		ActionData* action = m_actionStack.top();
		m_actionStack.pop();
		
		CardData* cardData = action->GetCardObject()->GetCardData();
		CardEffectType effectType= cardData->GetCardEffect();
		switch (effectType)
		{
		case CardEffectType::Damage:
			action->GetTargetUnit()->Damage(cardData->GetEffectValue());
			break;
		}
	}
	m_currentTurn = TurnType::PLAYER1;
}
