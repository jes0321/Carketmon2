#pragma once
#include "Object.h"
class UnitStatData;
class UnitInfoObj : public Object
{
public:
	void SetInfo(UnitStatData* _statData) { m_statData = _statData; }
	void Render(HDC _hdc) override;
private:
	const wstring GetStatString();
private:
	UnitStatData* m_statData = nullptr;

	Vec2 m_defaultSize = { 20,20 };
	Vec2 m_bigSize = { 40,40 };
};

