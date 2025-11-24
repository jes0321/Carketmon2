#pragma once
class Texture;


class CardData
{
public:
	CardData();
	CardData(wstring _name, wstring _description, Texture* _pTexture,
		ElementType _cardType, CardEffectType _cardEffect, int _integerValue);
	~CardData();

public:
	// Getter
	const wstring& GetName() const { return m_name; }
	const wstring& GetDescription() const { return m_description; }
	Texture* GetTexture() const { return m_pTexture; }
	ElementType GetCardType() const { return m_cardType; }
	CardEffectType GetCardEffect() const { return m_cardEffect; }
	int GetEffectValue() const { return m_integerValue; }

private:
	wstring		m_name;				// 카드 이름
	wstring		m_description;		// 카드 설명
	Texture* m_pTexture;			// 카드 그림
	ElementType	m_cardType;			// 카드 타입
	CardEffectType	m_cardEffect;		// 카드 효과
	int			m_integerValue;		// 효과 수치 (데미지량, 힐량 등)
};

