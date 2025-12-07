#pragma once
class CardData;
class Texture;
class UnitData
{
public:
	UnitData(wstring _name,int _maxHp,int _atk,int _def,int _spd,ElementType _type,Texture* _tex);
	~UnitData();
public:
	CardData* GetCardRandom();
	wstring GetName() const { return m_name; }
	int GetMaxHp() const { return m_maxHp; }
	int GetAtk() const { return m_atk; }
	int GetDef() const { return m_def; }
	int GetSpeed() const { return m_speed; }
	void SetCard(CardData* card, int cnt);
	void UseCard(int index);

	vector<CardData*> GetDeck() const { return m_deck; }
	Texture* GetTexture() const { return m_pTexture; }
	ElementType GetElementType() const { return m_elementType; }
private:
	wstring m_name;
	int m_maxHp;
	int m_atk;
	int m_def;
	int m_speed;
	Texture* m_pTexture;
	ElementType m_elementType;
	vector<int> m_usedIndexs;
	vector<CardData*> m_deck;
};

