#pragma once
#include "Object.h"
class CardData;
class CardObject :public Object
{
public:
	CardObject() : m_isSelected(false), m_cardData(nullptr) {}
	void SetCardData(CardData* data) { m_cardData = data; }
	void Render(HDC _hdc) override;
	void SetSelect(bool _isSelect) { m_isSelected = _isSelect; };
	wstring GetCardName() const;
	wstring GetCardDescription() const;
	CardData* GetCardData() const { return m_cardData; }
private :
	bool m_isSelected;
	CardData* m_cardData;
};

