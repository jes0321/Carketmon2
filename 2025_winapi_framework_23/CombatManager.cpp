#include "pch.h"
#include "CombatManager.h"
#include "UnitManager.h"
#include "ActionData.h"
#include "CardData.h"
#include "UnitObject.h"


void CombatManager::Init()
{
	m_currentTurn = UnitType::PLAYER1;
	m_units.resize(3);
	for (int i = 0; i < 3; ++i)
	{
		m_units[i] = new UnitObject();
	}

	Vec2 size = { 32 * 2,32 * 2 };
	for (int i = 0; i < 2; ++i) {
		m_units[i]->SetSize(size*2.f);
		m_units[i]->SetPos({ 200.f + i * 300.f, (WINDOW_HEIGHT / 2.f) -50.f});
	}
	m_units[2]->SetSize(size*4.2f);
	m_units[2]->SetPos({ WINDOW_WIDTH - 250.f, (WINDOW_HEIGHT / 2.f)-250.f });// Enemy
	m_units[0]->SetSelect(true);
	for(int i=0; i< m_units.size(); ++i)
	{
		m_units[i]->SetUnitData(GET_SINGLE(UnitManager)->GetUnitRandom());
	}
}

void CombatManager::Render(HDC _hdc)
{
	for(auto unit : m_units)
	{
		unit->Render(_hdc);
	}
}

void CombatManager::AddAction(UnitType _target, int index)
{
	CardData* card = GetUnit(m_currentTurn)->GetCardInHand(index);
	ActionData* newAction = new ActionData(m_currentTurn, _target, card);
	m_actionQueue.push_back(newAction);

	GetUnit(_target)->Damage(card->GetEffectValue());
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
	for(auto unit : m_units)
	{
		unit->SetSelect(false);
	}
	GetUnit(m_currentTurn)->SetSelect(true);
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

void CombatManager::DamageUnit(ActionData* action)
{
	UnitObject* targetUnit = GetUnit(action->GetTargetUnit());
	UnitObject* ownerUnit = GetUnit(action->GetOwnerUnit());

	int dmg = (ownerUnit->GetStat(StatType::Attack))*0.7f;
	dmg += action->GetCardObject()->GetEffectValue();

	targetUnit->Damage(dmg);
}