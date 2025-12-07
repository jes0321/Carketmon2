#pragma once
#include "Object.h"
#include "UnitData.h"
class HealthBar;
class CardData;
class UnitStatData;
class UnitObject : public Object
{
public:
	void Render(HDC _hdc) override;
	void Update() override;
	void SetUnitData(UnitData* _data);
	void SetBuffStat(StatType _type, int _value);
	void UseCard(int index);
	bool Damage(int dmg, ElementType _type, bool _isPowerup);
	void Heal(int heal, bool _floating = true);
	void SetSelect(bool isSelect) { m_isSelect = isSelect; }
	void SetPowerup(bool isPowerup) { m_isPowerup = isPowerup; }
	void SetSheilded(bool isSheilded) { m_isSheilded = isSheilded; }
	UnitStatData* GetStatData() const { return m_statData; }
	UnitData* GetUnitData() const { return m_unitData; }
	CardData* GetCardRandom() const { return m_unitData->GetCardRandom(); }
	CardData* GetCardInHand(int index) const { return m_handCards[index]; }
	vector<CardData*> GetHandCards() const { return m_handCards; }

	bool IsPowerup() const { return m_isPowerup; }
	int GetCurrentHp() const { return m_currentHp; }
	int GetStat(StatType _type) const;
	bool IsStrongAgainst(ElementType attacker) const;
	bool IsWeakAgainst(ElementType attacker) const;

	// 리바이브 연출
	void StartRevive();

private:
	// 내부 헬퍼로 묶어서 정리
	void InitHealthBar(const Vec2& pos, const Vec2& size);
	void InitStats();
	void UpdateBlink(float dt);
	void UpdateRevive(float dt);
	void RenderSelection(HDC _hdc, const Vec2& pos, const Vec2& size);
	void RenderTexture(HDC _hdc, const Vec2& pos, const Vec2& size, Texture* tex);
	void SyncHealthBar(const Vec2& pos, const Vec2& size, float liftY);
	void RenderNameLeftOfBar(HDC _hdc, const wstring& name, float barW, float barH, float barY, float posX);

private:
	bool m_isSheilded = false;
	bool m_isPowerup = false;
	bool m_isSelect = false;
	vector<CardData*> m_handCards;
	int m_currentHp = 0;
	UnitData* m_unitData = nullptr;
	UnitStatData* m_statData = nullptr;
	HealthBar* m_healthBar = nullptr;

	// 블링크 상태
	bool  m_isBlinking     = false;
	bool  m_isBlinkVisible = true;
	float m_blinkRemain    = 0.f;
	float m_blinkAccum     = 0.f;
	float m_blinkInterval  = 0.08f;

	// 리바이브 상태
	bool  m_isReviving     = false;
	float m_reviveTimeLeft = 0.f;
	float m_reviveDuration = 1.5f;
	float m_reviveLift     = 15.f;
};
