#include "pch.h"
#include "BattleEndScene.h"
#include "SceneManager.h"
#include "CombatManager.h"

void BattleEndScene::Init()
{
	bool isWin = GET_SINGLE(CombatManager)->IsWin();
	GET_SINGLE(CombatManager)->SetPosition(false);

	if (isWin) {
		m_resultText = L"승리!";
	}
	else {
		m_resultText = L"패배..";
	}
}

void BattleEndScene::Render(HDC _hdc)
{
	Scene::Render(_hdc);
	GET_SINGLE(CombatManager)->Render(_hdc);


	{
		GDISelector fontSelector(_hdc, FontType::PIXEL_BIG);
		SetBkMode(_hdc, TRANSPARENT);
		SetTextColor(_hdc, RGB(50, 50, 50));

		RECT textRect;
		textRect.left = 0;
		textRect.right = WINDOW_WIDTH;
		textRect.top = 100;  // 위쪽 여백
		textRect.bottom = 200;

		DrawTextW(_hdc, m_resultText.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
	}

}
