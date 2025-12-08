#include "pch.h"
#include "CardData.h"


static const wchar_t* ToStatName(StatType t)
{
	switch (t)
	{
	case StatType::Attack:  return L"공격력";
	case StatType::Defense: return L"방어력";
	case StatType::Speed:   return L"속도";
	default:                return L"알수없음";
	}
}

CardData::CardData(wstring _name, Texture* _pTexture, ElementType _cardType, CardEffectType _cardEffect, int _integerValue,int _priority,StatType _statType)
{
	m_name = _name;
	m_pTexture = _pTexture;
	m_cardType = _cardType;
	m_cardEffect = _cardEffect;
	m_integerValue = _integerValue;
	m_priority = _priority;
	m_statType = _statType;
	
	m_description = std::format(L"타입 : {}\n위력 : {}\n우선도 : {}\n 효과 : {}"
		, ToElementName(m_cardType)
		, m_integerValue
		, m_priority
		,ToEffectDesc());
}

wstring CardData::ToEffectDesc()
{
	switch (m_cardEffect)
	{
	case CardEffectType::Damage:   return L"대상을 공격합니다.";
	case CardEffectType::Heal:     return L"대상의 체력을 회복시킵니다.";
	case CardEffectType::StatBuff:     return std::format(L"대상의 {}을(를) {}칸 증가시킵니다.", ToStatName(m_statType), m_integerValue);
	case CardEffectType::StatDebuff:   return std::format(L"대상의 {}을(를) {}칸 감소시킵니다.", ToStatName(m_statType), m_integerValue);
	case CardEffectType::Buff:     return L"대상의 이번 턴 데미지를 증가시킵니다.";
	case CardEffectType::AoE:      return L"두명의 적을 공격합니다.";
	case CardEffectType::Shield:   return L"공격을 방어합니다.";
	case CardEffectType::Focus:    return L"모든 공격이 나를 향해 옵니다.";
	default:                       return L"효과 설명 없음.";
	}
}
