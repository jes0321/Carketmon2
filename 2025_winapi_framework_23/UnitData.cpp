#include "pch.h"
#include "UnitData.h"

#include <random>
#include <unordered_set>
#include <algorithm>
#include <vector>

UnitData::UnitData(wstring _name, int _maxHp, ElementType _type, Texture* _tex)
{
	m_name = _name;
	m_maxHp = _maxHp;
	m_elementType = _type;
	m_pTexture = _tex;
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

	// 랜덤 선택 (static으로 RNG를 유지)
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<size_t> dist(0, candidates.size() - 1);
	int chosenDeckIndex = candidates[dist(rng)];

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