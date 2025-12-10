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

	UnitData* data; 

	data = RegisterUnit(L"화격룡", L"Fire_Dragon", 75, 26, 10, 18, ElementType::Fire, UnitCategory::DEALER);
	data = RegisterUnit(L"불범", L"Fire_Bear", 85, 17, 16, 14, ElementType::Fire, UnitCategory::MULTI);
	data = RegisterUnit(L"파이츄", L"Fire_Rat", 60, 22, 8, 26, ElementType::Fire, UnitCategory::DEALER);
	data = RegisterUnit(L"불꽃부기", L"Fire_Turtle", 110, 12, 22, 8, ElementType::Fire, UnitCategory::TANK);
	
	data = RegisterUnit(L"빙란", L"Ice_Flower", 80, 16, 15, 13, ElementType::Ice, UnitCategory::SUPPORT);
	data = RegisterUnit(L"펭글레이즈", L"Ice_Penguin", 90, 18, 15, 14, ElementType::Ice, UnitCategory::MULTI);
	data = RegisterUnit(L"빙스타", L"Ice_Star", 70, 25, 10, 17, ElementType::Ice, UnitCategory::DEALER);
	data = RegisterUnit(L"폴리가온", L"Ice_Golem", 115, 11, 22, 9, ElementType::Ice, UnitCategory::TANK);
	 
	data = RegisterUnit(L"수르기", L"Water_Bird", 85, 18, 15, 14, ElementType::Water, UnitCategory::MULTI);
	data = RegisterUnit(L"피시키오스", L"Water_FishKing", 120, 10, 22, 8, ElementType::Water, UnitCategory::TANK);
	data = RegisterUnit(L"젤리킹", L"Water_JellyKing", 95, 17, 15, 12, ElementType::Water, UnitCategory::SUPPORT);
	data = RegisterUnit(L"문어소녀", L"Water_SquidGirl", 70, 26, 10, 20, ElementType::Water, UnitCategory::DEALER);
	 
	data = RegisterUnit(L"플로리나", L"Grass_Flower", 85, 17, 16, 13, ElementType::Grass, UnitCategory::SUPPORT);
	data = RegisterUnit(L"블룸맨", L"Grass_Bloom", 90, 18, 15, 15, ElementType::Grass, UnitCategory::MULTI);
	data = RegisterUnit(L"리프로스", L"Grass_LeafTank", 115, 11, 22, 9, ElementType::Grass, UnitCategory::TANK);
	data = RegisterUnit(L"바인서펀트", L"Grass_Serpent", 65, 23, 9, 26, ElementType::Grass, UnitCategory::DEALER);


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

UnitData* UnitManager::RegisterUnit(wstring _name, wstring _texName, int _maxHp, int _atk, int _def, int _spd, ElementType _type,UnitCategory _category)
{
	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(_texName);

	UnitData* unitData = new UnitData(_name,_maxHp,_atk,_def,_spd, _type,texture,_category);
	m_mapUnits.insert({ _name,unitData });
	return unitData;
}

