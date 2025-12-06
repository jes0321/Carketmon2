#pragma once
#include "CardData.h"
class CardManager
{
	DECLARE_SINGLE(CardManager);
public:
	void Init();
	void Release();
	CardData* GetCard(const wstring _cardName);
private:
	void RegisterCard(wstring _name, wstring _texName,
		ElementType _cardType, CardEffectType _cardEffect, int _integerValue);
private:
	std::unordered_map<wstring, CardData*> m_mapCards;
};

