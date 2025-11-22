#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Collider.h"
Projectile::Projectile()
	: m_angle(0.f)
	, m_dir{}
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
	auto* compo = AddComponent<Collider>();
	//GetComponent<Collider>()->SetSize({ 20.f,20.f });
	compo->SetSize({ 20.f,20.f });
	compo->SetName(L"PlayerBullet");
	compo->SetTrigger(true);
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	//Translate({ cosf(m_angle) * 500.f * fDT, sinf(m_angle) * 500.f * fDT});
	Translate({ m_dir.x * 500.f * fDT, m_dir.y * 500.f * fDT});
}

void Projectile::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	/*ELLIPSE_RENDER(_hdc, pos.x, pos.y
		, size.x, size.y);*/
	LONG width = m_pTex->GetWidth();
	LONG height = m_pTex->GetHeight();

	::TransparentBlt(_hdc
		, (int)(pos.x - size.x / 2)
		, (int)(pos.y - size.y / 2)
		, size.x
		, size.y
		, m_pTex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));

	ComponentRender(_hdc);

}
