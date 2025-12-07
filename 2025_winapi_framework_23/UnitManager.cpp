#include <fstream>
#include <sstream>
#include "pch.h"
#include "UnitData.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "CardManager.h"
#include "UnitManager.h"

void UnitManager::Init()
{
	CardManager* cardManager = GET_SINGLE(CardManager);

	UnitData* data = RegisterUnit(L"불꽃부기", L"Fire_Turtle", 60,22,6,12, ElementType::Fire);

	data->SetCard(cardManager->GetCard(L"파이어볼"),4);
	data->SetCard(cardManager->GetCard(L"화염방사"),4);
	data->SetCard(cardManager->GetCard(L"서핑"), 4);
	data->SetCard(cardManager->GetCard(L"물수리검"), 4);

	data = RegisterUnit(L"파이츄", L"Fire_Rat", 50,18,5,16,ElementType::Fire);

	data->SetCard(cardManager->GetCard(L"파이어볼"), 4);
	data->SetCard(cardManager->GetCard(L"화염방사"), 4);
	data->SetCard(cardManager->GetCard(L"서핑"), 4);
	data->SetCard(cardManager->GetCard(L"물수리검"), 4);

	data = RegisterUnit(L"물꼬부기", L"Water_FishFox", 80,12,16,7,ElementType::Water);
	data->SetCard(cardManager->GetCard(L"파이어볼"), 4);
	data->SetCard(cardManager->GetCard(L"화염방사"), 4);
	data->SetCard(cardManager->GetCard(L"서핑"), 4);
	data->SetCard(cardManager->GetCard(L"물수리검"), 4);

	data = RegisterUnit(L"잉어킹", L"Water_FishKing", 45,10,4,8,ElementType::Water);
	data->SetCard(cardManager->GetCard(L"파이어볼"), 4);
	data->SetCard(cardManager->GetCard(L"화염방사"), 4);
	data->SetCard(cardManager->GetCard(L"서핑"), 4);
	data->SetCard(cardManager->GetCard(L"물수리검"), 4);

	data = RegisterUnit(L"문어소녀", L"Water_SquidGirl", 55,12,10,10, ElementType::Water);
	data->SetCard(cardManager->GetCard(L"파이어볼"), 4);
	data->SetCard(cardManager->GetCard(L"화염방사"), 4);
	data->SetCard(cardManager->GetCard(L"서핑"), 4);
	data->SetCard(cardManager->GetCard(L"물수리검"), 4);
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

UnitData* UnitManager::GetUnitRandom()
{
	if (m_mapUnits.empty())
		return nullptr;

	// 전역 RNG 사용으로 교체
	std::uniform_int_distribution<int> dist(0, static_cast<int>(m_mapUnits.size()) - 1);
	const int randomIndex = dist(Random::Engine());

	auto iter = m_mapUnits.begin();
	std::advance(iter, randomIndex);
	return iter->second;
}

UnitData* UnitManager::RegisterUnit(wstring _name, wstring _texName, int _maxHp, int _atk, int _def, int _spd, ElementType _type)
{
	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(_texName);

	UnitData* unitData = new UnitData(_name,_maxHp,_atk,_def,_spd, _type,texture);
	m_mapUnits.insert({ _name,unitData });
	return unitData;
}

