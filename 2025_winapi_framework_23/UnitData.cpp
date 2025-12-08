#include "pch.h"
#include "UnitData.h"
#include "CardData.h"

#include <unordered_set>
#include <algorithm>
#include <vector>

static const wchar_t* ToCategory(UnitCategory t)
{
	switch (t)
	{
	case UnitCategory::DEALER:  return L"딜러";
	case UnitCategory::SUPPORT: return L"서포터";
	case UnitCategory::MULTI:   return L"복합";
	default:                 return L"Unknown";
	}
}
UnitData::UnitData(wstring _name, int _maxHp, int _atk,int _def,int _spd,ElementType _type, Texture* _tex,UnitCategory _category)
{
	m_name = _name;
	m_maxHp = _maxHp;
	m_atk = _atk;
	m_def = _def;
	m_speed = _spd;
	m_elementType = _type;
	m_pTexture = _tex;

	m_description = std::format(L"이름  : {}\n체력  : {}\n공격력 : {}\n방어력 : {}\n속도  : {}\n타입  : {}\n유형  : {}"
		, m_name
		, m_maxHp
		, m_atk
		, m_def
		, m_speed
		, CardData::ToElementName(m_elementType)
		, ToCategory(_category)
	);
}

UnitData::~UnitData()
{
	
}

CardData* UnitData::GetCardRandom()
{
	if (m_deck.empty())
		return nullptr;

	// 현재 사용중인 덱 인덱스를 집합으로 만들어 중복 검사 O(1)
	std::unordered_set<int> used(m_usedIndexs.begin(), m_usedIndexs.end());

	// 사용 가능한 인덱스 후보 수집
	std::vector<int> candidates;
	candidates.reserve(m_deck.size());
	for (int i = 0; i < static_cast<int>(m_deck.size()); ++i)
	{
		if (used.find(i) == used.end() && m_deck[i] != nullptr)
			candidates.push_back(i);
	}

	// 더 이상 가져올 카드가 없으면 nullptr 반환
	if (candidates.empty())
		return nullptr;

	std::uniform_int_distribution<size_t> dist(0, candidates.size() - 1);
	int chosenDeckIndex = candidates[dist(Random::Engine())];

	// 선택한 인덱스를 사용중 목록에 추가하고 카드 포인터 반환
	m_usedIndexs.push_back(chosenDeckIndex);
	return m_deck[chosenDeckIndex];
}

void UnitData::SetCard(CardData* card,int cnt)
{
	for (int i = 0; i < cnt; ++i) {
		if (card != nullptr)
		{
			m_deck.push_back(card);
		}
	}
}

void UnitData::UseCard(int index)
{
	// 전달된 인덱스와 일치하는 항목을 모두 제거
	m_usedIndexs.erase(std::remove(m_usedIndexs.begin(), m_usedIndexs.end(), index), m_usedIndexs.end());
}