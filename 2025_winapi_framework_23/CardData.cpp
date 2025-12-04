#include "pch.h"
#include "CardData.h"

CardData::CardData(wstring _name, wstring _description, Texture* _pTexture, ElementType _cardType, CardEffectType _cardEffect, int _integerValue,int _priority)
{
	m_name = _name;
	m_description = _description;
	m_pTexture = _pTexture;
	m_cardType = _cardType;
	m_cardEffect = _cardEffect;
	m_integerValue = _integerValue;
	m_priority = _priority;
}

