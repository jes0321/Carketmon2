#include "pch.h"
#include "Iamge.h"
#include "ResourceManager.h"

Image::Image(Texture* _texture)
{
	m_texture = _texture;
}

Image::~Image()
{
}

void Image::Render(HDC _hdc)
{
	if (m_texture == nullptr) return;

	Vec2 pos = GetPos();
	Vec2 size = GetSize();

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

