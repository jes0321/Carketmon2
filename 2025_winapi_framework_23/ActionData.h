#pragma once
class CardData;
class ActionData
{
public:
	ActionData(UnitType owner, UnitType target, CardData* card)
		: m_ownerUnit(owner)
		, m_targetUnit(target)
		, m_cardObject(card)
	{
	}
	UnitType GetOwnerUnit() const { return m_ownerUnit; }
	UnitType GetTargetUnit() const { return m_targetUnit; }
	CardData* GetCardObject() const { return m_cardObject; }
private:
	UnitType m_ownerUnit;
	UnitType m_targetUnit;
	CardData* m_cardObject;
};

