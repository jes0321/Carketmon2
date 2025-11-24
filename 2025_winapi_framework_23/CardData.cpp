#include "pch.h"
#include "CardData.h"

CardData::CardData()
	: m_name(L"")
	, m_description(L"")
	, m_pTexture(nullptr)
	, m_cardType(ElementType::Fire)
	, m_cardEffect(CardEffectType::Damage)
	, m_integerValue(0)
{
}
CardData::CardData(wstring _name, wstring _description, Texture* _pTexture, ElementType _cardType, CardEffectType _cardEffect, int _integerValue)
{
	m_name = _name;
	m_description = _description;
	m_pTexture = _pTexture;
	m_cardType = _cardType;
	m_cardEffect = _cardEffect;
	m_integerValue = _integerValue;
}
CardData::~CardData()
{
	
}

