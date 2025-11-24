#pragma once
#include "Scene.h"
class CardObject;
class TestScene : public Scene
{
public:
	void Init() override;
public:
	CardObject* GetCardObject(int index) const { return m_vecCards[index]; }
private :
	void UseCard(int index);
	void SetCard(CardObject* cardObj) { m_vecCards.push_back(cardObj); }
private :
	
	vector<CardObject*> m_vecCards;
};

