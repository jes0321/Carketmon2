#include "pch.h"
#include "UnitData.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "CardManager.h"
#include "UnitManager.h"

void UnitManager::Init()
{
	CardManager* cardManager = GET_SINGLE(CardManager);
	UnitData* data = RegisterUnit(L"Hero", L"HeroTex", 30, ElementType::Fire);

	data->SetCard(cardManager->GetCard(L"파이어볼"),5);
	data->SetCard(cardManager->GetCard(L"화염방사"),3);

	data = RegisterUnit(L"Slime", L"SlimeTex", 10, ElementType::Fire);

	data->SetCard(cardManager->GetCard(L"파이어볼"), 3);
	data->SetCard(cardManager->GetCard(L"화염방사"), 5);
}
void UnitManager::Release()
{
	for (auto& pair : m_mapUnits)
	{
		SAFE_DELETE(pair.second);
	}
	m_mapUnits.clear();
}

UnitData* UnitManager::GetUnit(const wstring _unitName)
{
	auto iter = m_mapUnits.find(_unitName);
	if (iter != m_mapUnits.end())
	{
		return iter->second;
	}
	return nullptr;
}

UnitData* UnitManager::RegisterUnit(wstring _name, wstring _texName, int _maxHp,ElementType _type)
{
	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(_texName);

	UnitData* unitData = new UnitData(_name,_maxHp,_type,texture);
	m_mapUnits.insert({ _name,unitData });
	return unitData;
}
