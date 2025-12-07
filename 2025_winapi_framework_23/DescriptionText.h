#pragma once
#include "Object.h"
class CardData;
class DescriptionText : public Object
{
public:
	void SetTargetCard(CardData* _cardObj) { m_targetCardObj = _cardObj; }
	void Render(HDC _hdc) override;
private:
	CardData* m_targetCardObj = nullptr;
};

