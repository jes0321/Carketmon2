#include "pch.h"
#include "CombatManager.h"
#include "UnitManager.h"
#include "ACtionData.h"
#include "UnitObject.h"

void CombatManager::Init()
{
	m_currentTurn = UnitType::PLAYER1;
	m_units.resize(3);
	for (int i = 0; i < 3; ++i)
	{
		m_units[i] = new UnitObject();
		m_units[i]->SetUnitData(GET_SINGLE(UnitManager)->GetUnitRandom());
	}
	
}

void CombatManager::AddAction(UnitType _target, int index)
{
	CardData* card = m_units[static_cast<int>(m_currentTurn)]->GetCardInHand(index);
	ActionData* newAction = new ActionData(m_currentTurn, _target, card);
	m_actionQueue.push_back(newAction);

	if(m_currentTurn==UnitType::PLAYER1)
	{
		m_currentTurn = UnitType::PLAYER2;
	}
	else if (m_currentTurn == UnitType::PLAYER2)
	{
		m_currentTurn = UnitType::ENEMY;
	}
	else if (m_currentTurn == UnitType::ENEMY)
	{
		m_currentTurn = UnitType::PLAYER1;
	}
}

void CombatManager::CancelAction(UnitType _ownerType)
{
	for(int i = 0; i < m_actionQueue.size(); ++i)
	{
		if(m_actionQueue[i]->GetOwnerUnit() == _ownerType)
		{
			m_actionQueue.erase(m_actionQueue.begin() + i);
			--i;
		}
	}
}

UnitObject* CombatManager::GetUnit(UnitType type)
{
	return m_units[static_cast<int>(type)];
}

vector<CardData*> CombatManager::GetHandCard()
{
	return m_units[static_cast<int>(m_currentTurn)]->GetHandCards();
}
