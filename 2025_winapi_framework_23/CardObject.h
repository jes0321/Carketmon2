#pragma once
#include "Object.h"
class CardData;
class CardObject :public Object
{
public:
	CardObject() : m_isSelected(false), m_cardData(nullptr) {}
	void SetCardData(CardData* data) { m_cardData = data; }
	void Render(HDC _hdc) override;
	void Update() override; // 선택 시 위로 호버링 애니메이션
	void SetSelect(bool _isSelect) { m_isSelected = _isSelect; };
	wstring GetCardName() const;
	wstring GetCardDescription() const;
	CardData* GetCardData() const { return m_cardData; }
private :
	bool m_isSelected;
	CardData* m_cardData;

	// Hovering 애니메이션 파라미터
	float m_hoverOffsetY = 0.f;   // 현재 상승 오프셋
	float m_hoverLift    = 30.f;  // 선택 시 들어올릴 높이(px)
	float m_hoverSpeed   = 10.f;  // 수렴 속도 계수

	// 선택 중 미세 바운스
	float m_bobTime      = 0.f;
	float m_bobAmp       = 3.f;   // 바운스 진폭(px)
	float m_bobSpeed     = 6.f;   // 바운스 속도(rad/s)
};

