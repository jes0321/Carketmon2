#include "pch.h"
#include "Texture.h";
#include "CardData.h"
#include "ResourceManager.h";
#include "CardManager.h"
void CardManager::Init()
{
	RegisterCard(L"불의강타", L"불의강타", ElementType::Fire, CardEffectType::Damage, 28);
	RegisterCard(L"얼음의강타", L"얼음의강타", ElementType::Ice, CardEffectType::Damage, 28);
	RegisterCard(L"물의강타", L"물의강타", ElementType::Water, CardEffectType::Damage, 28);
	RegisterCard(L"풀의강타", L"풀의강타", ElementType::Grass, CardEffectType::Damage, 28);

	RegisterCard(L"불의일격", L"불의일격", ElementType::Fire, CardEffectType::Damage, 20);
	RegisterCard(L"얼음의일격", L"얼음의일격", ElementType::Ice, CardEffectType::Damage, 20);
	RegisterCard(L"물의일격", L"물의일격", ElementType::Water, CardEffectType::Damage, 20);
	RegisterCard(L"풀의일격", L"풀의일격", ElementType::Grass, CardEffectType::Damage, 20);

	RegisterCard(L"화염폭발", L"화염폭발", ElementType::Fire, CardEffectType::AoE, 15);
	RegisterCard(L"한랭폭풍", L"한랭폭풍", ElementType::Ice, CardEffectType::AoE, 15);
	RegisterCard(L"물의해일", L"물의해일", ElementType::Water, CardEffectType::AoE, 15);
	RegisterCard(L"덩굴폭주", L"덩굴폭주", ElementType::Grass, CardEffectType::AoE, 15);

	RegisterCard(L"강힐", L"강힐", ElementType::Normal, CardEffectType::Heal, 15, 2);
	RegisterCard(L"약힐", L"약힐", ElementType::Normal, CardEffectType::Heal, 6, 2);

	RegisterCard(L"공격상승", L"공격상승", ElementType::Normal, CardEffectType::StatBuff, 2, 2, StatType::Attack);
	RegisterCard(L"방어상승", L"방어상승", ElementType::Normal, CardEffectType::StatBuff, 2, 2, StatType::Defense);
	RegisterCard(L"속도상승", L"속도상승", ElementType::Normal, CardEffectType::StatBuff, 2, 2, StatType::Speed);

	RegisterCard(L"공격하락", L"공격하락", ElementType::Normal, CardEffectType::StatDebuff, -2, 1, StatType::Attack);
	RegisterCard(L"방어하락", L"방어하락", ElementType::Normal, CardEffectType::StatDebuff, -2, 1, StatType::Defense);
	RegisterCard(L"속도하락", L"속도하락", ElementType::Normal, CardEffectType::StatDebuff, -2, 1, StatType::Speed);

	RegisterCard(L"도우미", L"도우미", ElementType::Normal, CardEffectType::Buff, 0, 5);
	RegisterCard(L"방어자세", L"방어자세", ElementType::Normal, CardEffectType::Shield, 2, 4);
	RegisterCard(L"날따름", L"날따름", ElementType::Normal, CardEffectType::Focus, 0, 4);

}
void CardManager::Release()
{
	for (auto& pair : m_mapCards)
	{
		SAFE_DELETE(pair.second);
	}
	m_mapCards.clear();
}
CardData* CardManager::GetCard(const wstring _cardName)
{
	auto iter = m_mapCards.find(_cardName);
	if (iter != m_mapCards.end())
		return iter->second;
	return nullptr;
}

void CardManager::RegisterCard(wstring _name,  wstring _texName,
	ElementType _cardType, CardEffectType _cardEffect, int _integerValue, int priority, StatType _statType)
{
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(_texName);
	CardData* newCard = new CardData(_name,tex,_cardType,_cardEffect,_integerValue,priority,_statType);
	m_mapCards.insert({ _name, newCard });
}
