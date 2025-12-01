#include "pch.h"
#include "Texture.h";
#include "CardData.h"
#include "ResourceManager.h";
#include "CardManager.h"
void CardManager::Init()
{
	//여기다 이제 카드 생기는 데이터 전부다 넣으면 됨
	RegisterCard(L"파이어볼",L"선택 유닛을 30 치유합니다.",L"Fireball",
		ElementType::Fire, CardEffectType::Damage, 30);
	RegisterCard(L"화염방사", L"적에게 20 데미지를 입힙니다.", L"Flamethrower",
		ElementType::Fire, CardEffectType::Damage, 20);
	RegisterCard(L"서핑", L"적에게 40 데미지를 입힙니다.", L"WaterSurfing",
		ElementType::Water, CardEffectType::Damage, 20);
	RegisterCard(L"물대포", L"적에게 10 데미지를 입힙니다.", L"WaterCannon",
		ElementType::Water, CardEffectType::Damage, 20);
	RegisterCard(L"물수리검", L"적에게 30 데미지를 입힙니다.", L"WaterShuriken",
		ElementType::Water, CardEffectType::Damage, 20);
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

void CardManager::RegisterCard(wstring _name, wstring _description, wstring _texName,
	ElementType _cardType, CardEffectType _cardEffect, int _integerValue)
{
	Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(_texName);
	CardData* newCard = new CardData(_name, _description,tex,_cardType,_cardEffect,_integerValue);
	m_mapCards.insert({ _name, newCard });
}
