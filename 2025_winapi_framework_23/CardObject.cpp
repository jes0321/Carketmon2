#include "pch.h"
#include "CardData.h"
#include "Texture.h"
#include "CardObject.h"

void CardObject::Update()
{
	// 목표 오프셋: 선택이면 위로 들어올림, 아니면 원위치
	const float target = m_isSelected ? m_hoverLift : 0.f;
	// 부드럽게 보간(지수 수렴)
	const float k = std::clamp(m_hoverSpeed * fDT, 0.f, 1.f);
	m_hoverOffsetY += (target - m_hoverOffsetY) * k;

	// 선택 중에는 약간의 바운스 처리
	if (m_isSelected)
		m_bobTime += fDT;
	else
		m_bobTime = 0.f;
}

void CardObject::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	// 선택 사각형 대신 위로 호버링된 위치로 렌더
	const float bob = m_isSelected ? std::sin(m_bobTime * m_bobSpeed) * m_bobAmp : 0.f;
	const float renderY = pos.y - (m_hoverOffsetY + bob);

	if (m_cardData == nullptr || m_cardData->GetTexture() == nullptr)
	{
		// 플레이스홀더 테두리 (호버링 적용된 위치로 그림)
		GDISelector penSel(_hdc, PenType::RED);
		GDISelector brushSel(_hdc, BrushType::HOLLOW);
		RECT_RENDER(_hdc, pos.x, renderY, size.x, size.y);
		return;
	}

	Texture* tex = m_cardData->GetTexture();
	LONG width = tex->GetWidth();
	LONG height = tex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(renderY - size.y / 2) // 호버링 적용
		, (int)size.x
		, (int)size.y
		, tex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}

wstring CardObject::GetCardName() const
{
	if(m_cardData!=nullptr)
	{
		return m_cardData->GetName();
	}
	return L"";
}

wstring CardObject::GetCardDescription() const
{
	if (m_cardData!=nullptr)
		return m_cardData->GetDescription();
	return L"";
}
