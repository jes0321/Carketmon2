#pragma once
class Texture;


class CardData
{
public:
	CardData(wstring _name,Texture* _pTexture,
		ElementType _cardType, CardEffectType _cardEffect, int _integerValue,int _priority=0,StatType _statType = StatType::Attack);
public:
	// Getter
	const wstring& GetName() const { return m_name; }
	const wstring& GetDescription() const { return m_description; };
	Texture* GetTexture() const { return m_pTexture; }
	ElementType GetCardType() const { return m_cardType; }
	CardEffectType GetCardEffect() const { return m_cardEffect; }
	StatType GetStatType() const { return m_statType; }
	int GetEffectValue() const { return m_integerValue; }
	int GetPriority() const { return m_priority; }
private:
	wstring ToEffectDesc();

private:
	wstring		m_name;				// 카드 이름
	wstring		m_description;		// 카드 설명
	Texture* m_pTexture;			// 카드 그림
	ElementType	m_cardType;			// 카드 타입
	CardEffectType	m_cardEffect;		// 카드 효과
	StatType 	m_statType;			// 효과 대상 능력치 (버프/디버프인 경우)
	int			m_integerValue;		// 효과 수치 (데미지량, 힐량 등)
	int m_priority = 0;
};

