#pragma once
#include "Object.h"
class LifeUI : public Object
{
public:
	void Init();
	void Render(HDC _hdc) override;
private :
	int m_lifeCount = 3;
};

