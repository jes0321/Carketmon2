#pragma once
#include "Object.h"
class CardObject;
class DescriptionText : public Object
{
public:
	void SetTargetCard(CardObject* _cardObj) { m_targetCardObj = _cardObj; }
	void Render(HDC _hdc) override;
private:
	CardObject* m_targetCardObj = nullptr;
};

