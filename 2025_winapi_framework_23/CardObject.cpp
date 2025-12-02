#include "pch.h"
#include "CardData.h"
#include "Texture.h"
#include "CardObject.h"


void CardObject::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	if (m_isSelected)
	{
		// 초록 테두리, 속 빈 브러시로 윤곽선만
		GDISelector penSel(_hdc, PenType::GREEN);
		GDISelector brushSel(_hdc, BrushType::HOLLOW);


		RECT_RENDER(_hdc, pos.x, pos.y, size.x * 1.03, size.y * 1.03);
	}
	if (m_cardData == nullptr || m_cardData->GetTexture() == nullptr)
	{
		// 플레이스홀더 테두리
		GDISelector penSel(_hdc, PenType::RED);
		GDISelector brushSel(_hdc, BrushType::HOLLOW);
		RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
		return;
	}
	Texture* tex = m_cardData->GetTexture();
	LONG width = tex->GetWidth();
	LONG height = tex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
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
