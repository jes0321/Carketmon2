#pragma once
class UnitObject;
class CardObject;
class ActionData
{
public:
	ActionData(UnitObject* owner, UnitObject* target, CardObject* card,TurnType _turn)
		: m_ownerUnit(owner)
		, m_targetUnit(target)
		, m_cardObject(card)
		, m_turnType(_turn)
	{
	}
	TurnType GetTurnType() const { return m_turnType; }
	UnitObject* GetOwnerUnit() const { return m_ownerUnit; }
	UnitObject* GetTargetUnit() const { return m_targetUnit; }
	CardObject* GetCardObject() const { return m_cardObject; }
private:
	TurnType m_turnType;
	UnitObject* m_ownerUnit;
	UnitObject* m_targetUnit;
	CardObject* m_cardObject;
};

