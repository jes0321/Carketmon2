#pragma once
#include "Object.h"
class Stage : 
	public Object
{
public:
	Stage();
	~Stage();
public:
	void Render(HDC _hdc);
	void Update() override;
public:
	bool isSeleted = false;
};

