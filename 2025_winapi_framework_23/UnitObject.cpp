#include "pch.h"
#include "Texture.h"
#include "UnitData.h"
#include "UnitObject.h"

void UnitObject::SetUnitData(UnitData* _data)
{
	m_unitData = _data;
	m_currentHp = m_unitData->GetMaxHp();
}

void UnitObject::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();

	Texture* tex = m_unitData->GetTexture();
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
