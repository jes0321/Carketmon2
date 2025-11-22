#include "pch.h"
#include "Floor.h"
#include "Collider.h"
Floor::Floor()
{
	auto* compo = AddComponent<Collider>();
	compo->SetSize({ 1000.f, 50.f });
	compo->SetName(L"Floor");
}

Floor::~Floor()
{
}

void Floor::Update()
{
}

void Floor::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}
