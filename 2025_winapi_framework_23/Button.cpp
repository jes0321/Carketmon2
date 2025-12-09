#include "pch.h"
#include "Button.h"
#include "ResourceManager.h"

Button::Button()
{
}

Button::~Button()
{
}

void Button::Render(HDC _hdc)
{
	switch (m_buttonState)
	{
	case Default:
		if(m_defaultTexture != nullptr)
			m_currnetTexture = m_defaultTexture;
		break;
	case Clicked:
		if (m_clickedTexture != nullptr)
			m_currnetTexture = m_clickedTexture;
		break;
	case Selected:
		if (m_selectedTexture != nullptr)
			m_currnetTexture = m_selectedTexture;
		break;
	}

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	if (m_isViewRect)
	{
		RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
	}

	if (m_currnetTexture == nullptr) return;

	LONG width = m_currnetTexture->GetWidth();
	LONG height = m_currnetTexture->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, (int)size.x
		, (int)size.y
		, m_currnetTexture->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}

void Button::Update()
{

}
