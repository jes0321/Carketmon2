#include "pch.h"
#include "LifeUI.h"
#include "CombatManager.h"
void LifeUI::Init()
{
	m_lifeCount = GET_SINGLE(CombatManager)->GetLifeCount();
}
void LifeUI::Render(HDC _hdc)
{
	for(int i=0; i<m_lifeCount; ++i)
	{
		// 하트 그리기
		// 위치: (20 + i*40, 20), 크기: (32,32)
		GDISelector brushSel(_hdc, BrushType::RED);
		ELLIPSE_RENDER(_hdc, 20 + i * 40, 20, 32, 32);
	}
}
