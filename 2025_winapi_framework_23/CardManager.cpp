#include "pch.h"
#include "Texture.h";
#include "CardData.h"
#include "ResourceManager.h";
#include "CardManager.h"
void CardManager::Init()
{
	RegisterCard(L"작열펀치", L"Fireball",
		ElementType::Fire, CardEffectType::Damage, 18);

	RegisterCard(L"물수리검", L"WaterShuriken",
		ElementType::Water, CardEffectType::Damage, 18);

	RegisterCard(L"리프컷", L"CuttingGrass",
		ElementType::Grass, CardEffectType::Damage, 18);

	RegisterCard(L"서리조각", L"Ice_Piece",
		ElementType::Ice, CardEffectType::Damage, 18);


	RegisterCard(L"화염화살", L"FireArrow",
		ElementType::Fire, CardEffectType::Damage, 27);

	RegisterCard(L"워터캐논", L"WaterCannon",
		ElementType::Water, CardEffectType::Damage, 27);

	RegisterCard(L"맹독덩굴", L"PoisonThorn",
		ElementType::Grass, CardEffectType::Damage, 27);

	RegisterCard(L"빙결수리검", L"Ice_Shuriken",
		ElementType::Ice, CardEffectType::Damage, 27);


	RegisterCard(L"플레어스톰", L"Flamethrower",
		ElementType::Fire, CardEffectType::AoE, 15);

	RegisterCard(L"파도타기", L"WaterSurfing",
		ElementType::Water, CardEffectType::AoE, 15);

	RegisterCard(L"덩굴폭풍", L"ThornVine",
		ElementType::Grass, CardEffectType::AoE, 15);

	RegisterCard(L"서리떨어지기", L"Icicle",
		ElementType::Ice, CardEffectType::AoE, 15);


	RegisterCard(L"응급치료", L"Heel",
		ElementType::Normal, CardEffectType::Heal, 30,1);

	RegisterCard(L"대치유", L"Heel_Strong",
		ElementType::Normal, CardEffectType::Heal, 55, 1);


	RegisterCard(L"속력증폭", L"Buff_Speed",
		ElementType::Normal, CardEffectType::StatBuff, 2, 2, StatType::Speed);

	RegisterCard(L"공격강화", L"Buff_Attack",
		ElementType::Normal, CardEffectType::StatBuff, 2, 2, StatType::Attack);

	RegisterCard(L"방어강화", L"Buff_Defense",
		ElementType::Normal, CardEffectType::StatBuff, 2, 2, StatType::Defense);


	RegisterCard(L"속력저하", L"Debuff_Speed",
		ElementType::Normal, CardEffectType::StatDebuff, -1, 1, StatType::Speed);

	RegisterCard(L"위력감쇠", L"Debuff_Attack",
		ElementType::Normal, CardEffectType::StatDebuff, -1, 1, StatType::Attack);

	RegisterCard(L"수비붕괴", L"Debuff_Defense",
		ElementType::Normal, CardEffectType::StatDebuff, -1, 1, StatType::Defense);


	RegisterCard(L"전력지원", L"Buff",
		ElementType::Normal, CardEffectType::Buff, 0, 5);

	RegisterCard(L"방어태세", L"Defense",
		ElementType::Normal, CardEffectType::Shield, 0, 4);

	RegisterCard(L"따라와!", L"FollowMe",
		ElementType::Normal, CardEffectType::Focus, 0, 4);
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
