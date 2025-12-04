#pragma once
#include "UnitObject.h"
#include "CardData.h"
class ActionData
{
public:
	ActionData(UnitObject* owner, UnitObject* target, CardData* card)
		: m_ownerUnit(owner)
		, m_targetUnit(target)
		, m_cardObject(card)
	{
	}
	int GetPriority() const { return m_cardObject->GetPriority(); }
	int GetSpeed() const { return m_ownerUnit->GetStat(StatType::Speed); }
	UnitObject* GetOwnerUnit() const { return m_ownerUnit; }
	UnitObject* GetTargetUnit() const { return m_targetUnit; }
	CardData* GetCardObject() const { return m_cardObject; }
	static bool OrderPtr(const ActionData* a, const ActionData* b)
	{
		if (a->GetPriority() != b->GetPriority())
			return a->GetPriority() > b->GetPriority();
		return a->GetSpeed() > b->GetSpeed();
	}
private:
	UnitObject* m_ownerUnit;
	UnitObject* m_targetUnit;
	CardData* m_cardObject;
};

