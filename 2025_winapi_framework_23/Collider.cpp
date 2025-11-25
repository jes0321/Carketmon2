#include "pch.h"
#include "Collider.h"
#include "Object.h"
UINT Collider::m_nextID = 0;
Collider::Collider()
	: m_ID(m_nextID++)
	, m_showDebug(false)
	, m_name{}
	, m_isTrigger(false)
{
}
Collider::~Collider()
{
}
void Collider::Init()
{
	m_size = { 30.f,30.f };
	m_updatedPos = { 0.f, 0.f };
	m_offsetPos = { 0.f, 0.f };
}

void Collider::LateUpdate()
{
	Object* owner = GetOwner();
	Vec2 pos = owner->GetPos();
	m_updatedPos = pos + m_offsetPos;
}

void Collider::Render(HDC _hdc)
{
	::TextOut(_hdc, 0, 0, L"¾È³ç", 2);
	GDISelector font(_hdc, FontType::TITLE);
	::TextOut(_hdc, 10, 10, L"ÇÏ¼À", 2);
	PenType penColor = PenType::GREEN;
	if (m_showDebug)
		penColor = PenType::RED;
	// »ç°¢Çü
	GDISelector pen(_hdc, penColor);
	GDISelector brush(_hdc, BrushType::HOLLOW);
	RECT_RENDER(_hdc, m_updatedPos.x, m_updatedPos.y, m_size.x ,m_size.y);
}

void Collider::EnterCollision(Collider* _other)
{
	m_showDebug = true;
}

void Collider::StayCollision(Collider* _other)
{
}

void Collider::ExitCollision(Collider* _other)
{
	m_showDebug = false;
}
