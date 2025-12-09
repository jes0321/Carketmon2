#include "pch.h"
#include "Image.h"
#include "ResourceManager.h"

Image::Image()
{

}

Image::~Image()
{
}

void Image::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	
	if (m_texture == nullptr)
	{
		RECT_RENDER(_hdc, pos.x, pos.y, size.x, size.y);
		return;
	}

	LONG width = m_texture->GetWidth();
	LONG height = m_texture->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, (int)size.x
		, (int)size.y
		, m_texture->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));
}

void Image::Update()
{
}

