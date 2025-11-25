#include "pch.h"
#include "TestEffect.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
TestEffect::TestEffect()
	: m_pTexture(nullptr)
{
	m_pTexture = GET_SINGLE(ResourceManager)->GetTexture(L"TestEffect_128_32");
	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(L"TestEffect"
		, m_pTexture
		, { 0.f,0.f }
		, { 64.f,64.f }
		, { 64.f,0.f }
	, 4, 0.1f);
	animator->Play(L"TestEffect");
}

TestEffect::~TestEffect()
{
	//SAFE_DELETE(m_pTexture);
}

void TestEffect::Render(HDC _hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	int width = m_pTexture->GetWidth();
	int height = m_pTexture->GetHeight();
}

void TestEffect::Update()
{

}

