#pragma once
#include "Object.h"
#include "Texture.h"

class Image :
    public Object
{
public:
	Image();
	~Image();
public:
	void Render(HDC _hdc);
	void Update() override;
public:
	void SetTexture(Texture* _texture) { m_texture = _texture; }
	Texture* GetTexture() { return m_texture; }
private:
	Texture* m_texture = nullptr;
};

