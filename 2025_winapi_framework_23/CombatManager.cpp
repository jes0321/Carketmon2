#include "pch.h"
#include "CombatManager.h"
#include "UnitManager.h"
#include "ActionData.h"
#include "CardData.h"
#include "UnitObject.h"
#include "SceneManager.h"
#include "BattleScene.h"
#include "BattleDescription.h"
#include "StageManager.h"

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
		m_units[i]->SetSize(size * 2.f);
		m_units[i]->SetPos({ 200.f + i * 300.f, (WINDOW_HEIGHT / 2.f) - 50.f });
	}
	m_units[2]->SetSize(size * 4.2f);
	m_units[2]->SetPos({ WINDOW_WIDTH - 250.f, (WINDOW_HEIGHT / 2.f) - 250.f });// Enemy
	m_units[0]->SetSelect(true);
	for (int i = 0; i < 2; ++i)
	{
		m_units[i]->SetUnitData(GET_SINGLE(UnitManager)->GetUnitRandom());
	}
}
void CombatManager::Update() {
	for (int i = 0; i < m_units.size(); ++i)
	{
		m_units[i]->Update();
	}
	if (m_isWait) {
		m_timer += fDT;
		if (m_timer >= m_delayTime) {
			BattleScene* battleScene = GET_SINGLE(SceneManager)->GetBattleScene();
			if (m_actionList.size() <= 0) {
				m_isWait = false;
				battleScene->SetWaitTurn(false);
				battleScene->SetCardData();
				for (int i = 0; i < m_units.size(); ++i)
				{
					m_units[i]->SetPowerup(false);
					m_units[i]->SetSheilded(false);
				}
				return;
			}
			m_timer = 0;
			ActionData* action = m_actionList.front();
			battleScene->SetDes(action);
			switch (action->GetCardObject()->GetCardEffect())
			{
			case CardEffectType::Damage: DamageUnit(action); break;
			case CardEffectType::Heal: HealUnit(action); break;
			case CardEffectType::StatBuff: StatControl(action); break;
			case CardEffectType::StatDebuff: StatControl(action); break;
			case CardEffectType::Buff: BuffTarget(action); break;
			case CardEffectType::Shield:
				action->GetTargetUnit()->SetSheilded(true);
				break;
			case CardEffectType::AoE: DamageUnit(action); break;
			}
			action->UseCard();
			m_actionList.erase(m_actionList.begin());
		}
	}
}

void CombatManager::Render(HDC _hdc)
{
	for (auto unit : m_units)
	{
		unit->Render(_hdc);
	}
}

void CombatManager::SetEnemy(UnitData* _data)
{
	GetUnit(UnitType::ENEMY)->SetUnitData(_data);
}

void CombatManager::EndTurn()
{
	BattleScene* battleScene = GET_SINGLE(SceneManager)->GetBattleScene();
	battleScene->SetWaitTurn(true);

	EnemyTurn();

	sort(m_actionList.begin(), m_actionList.end(), ActionData::OrderPtr);

	m_timer = m_delayTime / 2;
	m_isWait = true;
}

void CombatManager::AddAction(UnitType _target, int index)
{
	UnitObject* current = GetUnit(m_currentTurn);
	if (_target == UnitType::SELF)
	{
		_target = m_currentTurn;
	}
	UnitObject* target = GetUnit(_target);

	CardData* card = current->GetCardInHand(index);

	ActionData* newAction = new ActionData(current, target, card,index);
	m_actionList.push_back(newAction);

	m_currentTurn = UnitType(((UINT)(m_currentTurn)) + 1);

	if (m_currentTurn == UnitType::ENEMY)
	{
		EndTurn();
		m_currentTurn = UnitType::PLAYER1;
	}

	for (auto unit : m_units)
	{
		unit->SetSelect(false);
	}
	GetUnit(m_currentTurn)->SetSelect(true);
}

void CombatManager::CancelAction(UnitType _ownerType)
{
	for (int i = 0; i < m_actionList.size(); ++i)
	{
		if (m_actionList[i]->GetOwnerUnit() == GetUnit(_ownerType))
		{
			m_actionList.erase(m_actionList.begin() + i);
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

void CombatManager::EnemyTurn()
{
	UnitObject* enemy = GetUnit(UnitType::ENEMY);
	int idx = rand() % 4;
	CardData* card = enemy->GetCardInHand(idx);
	CardEffectType effectType = card->GetCardEffect();
	if (effectType == CardEffectType::AoE) {
		for (int i = 0; i < 2; ++i) {
			m_actionList.push_back(new ActionData(enemy, m_units[i], card, idx));
		}
	}
	else if(effectType== CardEffectType::Heal || effectType== CardEffectType::StatBuff || effectType== CardEffectType::Shield) {
		m_actionList.push_back(new ActionData(enemy, enemy, card, idx));
	}
	else {
		UnitObject* target = m_units[rand() % 2];
		m_actionList.push_back(new ActionData(enemy, target, card, idx));
	}
}

void CombatManager::DamageUnit(ActionData* action)
{
	UnitObject* targetUnit = action->GetTargetUnit();
	UnitObject* ownerUnit = action->GetOwnerUnit();

	int dmg = (ownerUnit->GetStat(StatType::Attack)) * 0.7f;
	dmg += action->GetCardObject()->GetEffectValue();

	targetUnit->Damage(dmg, ownerUnit->GetUnitData()->GetElementType(), targetUnit->IsPowerup());
}

void CombatManager::HealUnit(ActionData* action)
{
	UnitObject* targetUnit = action->GetTargetUnit();
	UnitObject* ownerUnit = action->GetOwnerUnit();
	int heal = action->GetCardObject()->GetEffectValue();
	heal += ownerUnit->GetStat(StatType::Attack) * 0.3f;
	targetUnit->Heal(heal);
}

void CombatManager::StatControl(ActionData* action)
{
	UnitObject* targetUnit = action->GetTargetUnit();
	int buffValue = action->GetCardObject()->GetEffectValue();
	StatType statType = action->GetCardObject()->GetStatType();
	targetUnit->SetBuffStat(statType, buffValue);
}

void CombatManager::BuffTarget(ActionData* action)
{
	UnitObject* targetUnit = action->GetTargetUnit();
	targetUnit->SetPowerup(true);
}
