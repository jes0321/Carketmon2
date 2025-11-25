#pragma once
#include "Object.h"
class Texture;
class TestEffect : public Object
{
public:
	TestEffect();
	~TestEffect();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	Texture* m_pTexture;
};


