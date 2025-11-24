#pragma once
#include "Object.h"
class CardData;
class CardObject :public Object
{
public:
	void SetCardData(CardData* data) { m_cardData = data; }
	void Render(HDC _hdc) override;
	CardData* GetCardData() const { return m_cardData; }
private :
	CardData* m_cardData;
};

