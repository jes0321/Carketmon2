#pragma once
class CardData;
class Texture;
class UnitData
{
public:
	UnitData(wstring _name,int _maxHp,ElementType _type,Texture* _tex);
	~UnitData();
public:
	CardData* GetCardRandom();
	int GetMaxHp() const { return m_maxHp; }
	void SetCard(CardData* card, int cnt);
	void UseCard(int index);
	Texture* GetTexture() const { return m_pTexture; }
private:
	wstring m_name;
	int m_maxHp;
	Texture* m_pTexture;
	ElementType m_elementType;
	vector<int> m_usedIndexs;
	vector<CardData*> m_deck;
};

