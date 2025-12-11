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
	data = RegisterUnit(L"파이츄", L"Fire_Rat", 95, 27, 28, 25, ElementType::Fire, UnitCategory::SUPPORT);

	data->SetCard(cardManager->GetCard(L"따라와!"),2);
	data->SetCard(cardManager->GetCard(L"방어태세"),2);
	data->SetCard(cardManager->GetCard(L"전력지원"),2);

	data->SetCard(cardManager->GetCard(L"응급치료"));
	data->SetCard(cardManager->GetCard(L"대치유"),2);
	

	data->SetCard(cardManager->GetCard(L"속도저하"));
	data->SetCard(cardManager->GetCard(L"위력감쇠"),2);
	data->SetCard(cardManager->GetCard(L"수비붕괴"),2);


	data->SetCard(cardManager->GetCard(L"작열펀치"),2);


	data = RegisterUnit(L"용염갑", L"Fire_Turtle", 115, 23, 37, 20, ElementType::Fire, UnitCategory::TANK);

	data->SetCard(cardManager->GetCard(L"방어태세"));
	data->SetCard(cardManager->GetCard(L"따라와!"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"방어강화"), 2);

	data->SetCard(cardManager->GetCard(L"위력감쇠"), 2);
	data->SetCard(cardManager->GetCard(L"수비붕괴"));
	data->SetCard(cardManager->GetCard(L"속력저하"));

	data->SetCard(cardManager->GetCard(L"응급치료"), 2);
	data->SetCard(cardManager->GetCard(L"대치유"));


	data->SetCard(cardManager->GetCard(L"작열펀치"), 2);
	data->SetCard(cardManager->GetCard(L"서리조각"));


	data = RegisterUnit(L"화격룡", L"Fire_FightingDragon", 77, 43, 18, 40, ElementType::Fire, UnitCategory::DEALER);

	data->SetCard(cardManager->GetCard(L"화염화살"), 3);
	data->SetCard(cardManager->GetCard(L"작열펀치"), 2);
	data->SetCard(cardManager->GetCard(L"플레어스톰"));

	data->SetCard(cardManager->GetCard(L"물수리검"));
	data->SetCard(cardManager->GetCard(L"서리조각"));
	data->SetCard(cardManager->GetCard(L"리프컷"));

	data->SetCard(cardManager->GetCard(L"공격강화"), 2);
	data->SetCard(cardManager->GetCard(L"속력증폭"), 2);

	data->SetCard(cardManager->GetCard(L"응급치료"));

	data->SetCard(cardManager->GetCard(L"방어태세"), 2);

	data = RegisterUnit(L"화범", L"Fire_Fursealpng", 86, 32, 23, 30, ElementType::Fire, UnitCategory::MULTI);

	data->SetCard(cardManager->GetCard(L"따라와!"));
	data->SetCard(cardManager->GetCard(L"방어태세"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"응급치료"),2);

	data->SetCard(cardManager->GetCard(L"공격강화"),2);
	data->SetCard(cardManager->GetCard(L"속력증폭"));
	//data->SetCard(cardManager->GetCard(L"방어강화"));

	data->SetCard(cardManager->GetCard(L"속도저하"));
	data->SetCard(cardManager->GetCard(L"위력감쇠"),2);
	//data->SetCard(cardManager->GetCard(L"수비붕괴"));

	data->SetCard(cardManager->GetCard(L"작열펀치"), 2);
	data->SetCard(cardManager->GetCard(L"서리조각"));
	data->SetCard(cardManager->GetCard(L"화염화살"));

	data = RegisterUnit(L"어우린", L"Water_FishFox", 80, 40, 23, 37, ElementType::Water, UnitCategory::DEALER);

	data->SetCard(cardManager->GetCard(L"워터캐논"), 3);
	data->SetCard(cardManager->GetCard(L"물수리검"), 2);
	data->SetCard(cardManager->GetCard(L"파도타기"));

	data->SetCard(cardManager->GetCard(L"서리조각"));
	data->SetCard(cardManager->GetCard(L"작열펀치"));
	data->SetCard(cardManager->GetCard(L"리프컷"));

	data->SetCard(cardManager->GetCard(L"방어태세"), 2);

	data->SetCard(cardManager->GetCard(L"공격강화"), 2);
	data->SetCard(cardManager->GetCard(L"속력증폭"), 2);

	data->SetCard(cardManager->GetCard(L"응급치료"));


	data = RegisterUnit(L"어왕", L"Water_FishKing", 123, 18, 45, 18, ElementType::Water, UnitCategory::TANK);
	
	data->SetCard(cardManager->GetCard(L"방어태세"),2);
	data->SetCard(cardManager->GetCard(L"따라와!"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"방어강화"), 2);

	data->SetCard(cardManager->GetCard(L"속력저하"),2);
	data->SetCard(cardManager->GetCard(L"위력감쇠"));

	data->SetCard(cardManager->GetCard(L"응급치료"), 2);
	data->SetCard(cardManager->GetCard(L"대치유"));


	data->SetCard(cardManager->GetCard(L"물수리검"), 2);
	data->SetCard(cardManager->GetCard(L"리프컷"));

	data = RegisterUnit(L"문어링", L"Water_SquidGirl", 98, 23, 33, 23, ElementType::Water, UnitCategory::SUPPORT);

	data->SetCard(cardManager->GetCard(L"따라와!"), 2);
	data->SetCard(cardManager->GetCard(L"방어태세"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"), 2);

	data->SetCard(cardManager->GetCard(L"응급치료"));
	data->SetCard(cardManager->GetCard(L"대치유"), 2);


	data->SetCard(cardManager->GetCard(L"속도저하"),2);
	data->SetCard(cardManager->GetCard(L"위력감쇠"), 2);
	data->SetCard(cardManager->GetCard(L"수비붕괴"));


	data->SetCard(cardManager->GetCard(L"물수리검"), 2);

	data = RegisterUnit(L"해파제", L"Water_KingJellyfish", 92, 28, 16, 28, ElementType::Water, UnitCategory::MULTI);

	data->SetCard(cardManager->GetCard(L"따라와!"));
	data->SetCard(cardManager->GetCard(L"방어태세"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"응급치료"), 2);

	//data->SetCard(cardManager->GetCard(L"공격강화"));
	data->SetCard(cardManager->GetCard(L"속력증폭"));
	data->SetCard(cardManager->GetCard(L"방어강화"),2);

	data->SetCard(cardManager->GetCard(L"속도저하"));
	data->SetCard(cardManager->GetCard(L"위력감쇠"));
	data->SetCard(cardManager->GetCard(L"수비붕괴"));

	data->SetCard(cardManager->GetCard(L"물수리검"), 2);
	data->SetCard(cardManager->GetCard(L"워터캐논"));
	data->SetCard(cardManager->GetCard(L"리프컷"));

	data = RegisterUnit(L"펭서릿", L"Ice_Penguin", 125, 19, 42, 17, ElementType::Ice, UnitCategory::TANK);

	data->SetCard(cardManager->GetCard(L"방어태세"));
	data->SetCard(cardManager->GetCard(L"따라와!"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"방어강화"), 2);

	data->SetCard(cardManager->GetCard(L"위력감쇠"));
	data->SetCard(cardManager->GetCard(L"속력저하"),3);

	data->SetCard(cardManager->GetCard(L"응급치료"), 2);
	data->SetCard(cardManager->GetCard(L"대치유"));


	data->SetCard(cardManager->GetCard(L"서리조각"), 2);
	data->SetCard(cardManager->GetCard(L"물수리검"));

	data = RegisterUnit(L"빙스타", L"Ice_Star", 82, 41, 20, 37, ElementType::Ice, UnitCategory::DEALER);

	data->SetCard(cardManager->GetCard(L"빙결수리검"), 3);
	data->SetCard(cardManager->GetCard(L"서리조각"), 2);
	data->SetCard(cardManager->GetCard(L"서리떨어지기"));

	data->SetCard(cardManager->GetCard(L"물수리검"));
	data->SetCard(cardManager->GetCard(L"작열펀치"));
	data->SetCard(cardManager->GetCard(L"리프컷"));

	data->SetCard(cardManager->GetCard(L"방어태세"), 2);

	data->SetCard(cardManager->GetCard(L"공격강화"), 2);
	data->SetCard(cardManager->GetCard(L"속력증폭"), 2);

	data->SetCard(cardManager->GetCard(L"응급치료"));


	data = RegisterUnit(L"냉란", L"Ice_Egg", 105, 24, 30, 23, ElementType::Ice, UnitCategory::SUPPORT);

	data->SetCard(cardManager->GetCard(L"따라와!"), 2);
	data->SetCard(cardManager->GetCard(L"방어태세"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"), 2);

	data->SetCard(cardManager->GetCard(L"응급치료"));
	data->SetCard(cardManager->GetCard(L"대치유"), 2);


	data->SetCard(cardManager->GetCard(L"속도저하"),3);
	data->SetCard(cardManager->GetCard(L"위력감쇠"));
	data->SetCard(cardManager->GetCard(L"수비붕괴"));


	data->SetCard(cardManager->GetCard(L"서리조각"), 2);

	data = RegisterUnit(L"폴리가온", L"Ico_Polygon", 95, 28, 25, 27, ElementType::Ice, UnitCategory::MULTI);

	data->SetCard(cardManager->GetCard(L"따라와!"));
	data->SetCard(cardManager->GetCard(L"방어태세"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"응급치료"), 2);

	data->SetCard(cardManager->GetCard(L"공격강화"));
	data->SetCard(cardManager->GetCard(L"속력증폭"));
	data->SetCard(cardManager->GetCard(L"방어강화"));

	data->SetCard(cardManager->GetCard(L"속도저하"),2);
	data->SetCard(cardManager->GetCard(L"위력감쇠"));
	//data->SetCard(cardManager->GetCard(L"수비붕괴"));

	data->SetCard(cardManager->GetCard(L"서리조각"), 2);
	data->SetCard(cardManager->GetCard(L"물수리검"));
	data->SetCard(cardManager->GetCard(L"빙결수리검"));

	data = RegisterUnit(L"블로섬맨", L"Leaf_FlowerMan", 100, 24, 29, 27, ElementType::Grass, UnitCategory::SUPPORT);

	data->SetCard(cardManager->GetCard(L"따라와!"), 2);
	data->SetCard(cardManager->GetCard(L"방어태세"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"), 2);

	data->SetCard(cardManager->GetCard(L"응급치료"));
	data->SetCard(cardManager->GetCard(L"대치유"), 2);


	data->SetCard(cardManager->GetCard(L"속도저하"));
	data->SetCard(cardManager->GetCard(L"위력감쇠"), 2);
	data->SetCard(cardManager->GetCard(L"수비붕괴"), 2);


	data->SetCard(cardManager->GetCard(L"리프컷"), 2);

	data = RegisterUnit(L"리프맨", L"Leaf_Man", 120, 20, 38, 23, ElementType::Grass, UnitCategory::TANK);

	data->SetCard(cardManager->GetCard(L"방어태세"),2);
	data->SetCard(cardManager->GetCard(L"따라와!"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"방어강화"), 3);

	data->SetCard(cardManager->GetCard(L"위력감쇠"));
	data->SetCard(cardManager->GetCard(L"속력저하"));

	data->SetCard(cardManager->GetCard(L"응급치료"), 2);
	data->SetCard(cardManager->GetCard(L"대치유"));


	data->SetCard(cardManager->GetCard(L"리프컷"), 2);
	data->SetCard(cardManager->GetCard(L"작열펀치"));

	data = RegisterUnit(L"덩굴레스", L"Leaf_Vine", 89, 29, 24, 33, ElementType::Grass, UnitCategory::MULTI);

	data->SetCard(cardManager->GetCard(L"따라와!"));
	data->SetCard(cardManager->GetCard(L"방어태세"), 2);
	data->SetCard(cardManager->GetCard(L"전력지원"));

	data->SetCard(cardManager->GetCard(L"응급치료"), 2);

	data->SetCard(cardManager->GetCard(L"공격강화"));
	data->SetCard(cardManager->GetCard(L"속력증폭"),2);
	//data->SetCard(cardManager->GetCard(L"방어강화"));

	data->SetCard(cardManager->GetCard(L"위력감쇠"));
	data->SetCard(cardManager->GetCard(L"수비붕괴"),2);

	data->SetCard(cardManager->GetCard(L"리프컷"), 2);
	data->SetCard(cardManager->GetCard(L"물수리검"));
	data->SetCard(cardManager->GetCard(L"맹독덩굴"));

	data = RegisterUnit(L"플로리안", L"Leaf_Flower", 79, 39, 19, 43, ElementType::Grass, UnitCategory::DEALER);

	data->SetCard(cardManager->GetCard(L"맹독덩굴"), 3);     // 자속 강공
	data->SetCard(cardManager->GetCard(L"리프컷"), 2);        // 자속 약공
	data->SetCard(cardManager->GetCard(L"덩굴폭풍"));         // 자속 AoE

	data->SetCard(cardManager->GetCard(L"서리조각"));         // 타속 공
	data->SetCard(cardManager->GetCard(L"물수리검"));         // 타속 공
	data->SetCard(cardManager->GetCard(L"작열펀치"));         // 타속 공

	data->SetCard(cardManager->GetCard(L"방어태세"), 2);      // 방어 2
	data->SetCard(cardManager->GetCard(L"공격강화"), 2);      // 공 버프 2
	data->SetCard(cardManager->GetCard(L"속력증폭"), 2);      // 속 버프 2

	data->SetCard(cardManager->GetCard(L"응급치료"));          // 힐 1
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

UnitData* UnitManager::RegisterUnit(wstring _name, wstring _texName, int _maxHp, int _atk, int _def, int _spd, ElementType _type, UnitCategory _category)
{
	Texture* texture = GET_SINGLE(ResourceManager)->GetTexture(_texName);

	UnitData* unitData = new UnitData(_name, _maxHp, _atk, _def, _spd, _type, texture, _category);
	m_mapUnits.insert({ _name,unitData });
	return unitData;
}

