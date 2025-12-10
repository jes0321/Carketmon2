#include "pch.h"
#include "BattleEndScene.h"
#include "SceneManager.h"
#include "CombatManager.h"
#include "InputManager.h"
#include "Button.h"
#include "ButtonSwitcher.h"

void BattleEndScene::Init()
{
	m_isWin = GET_SINGLE(CombatManager)->IsWin();
	GET_SINGLE(CombatManager)->SetPosition(false);

	if (m_isWin) {
		m_resultText = L"승리!";

		ButtonSwitcher* btnManager = new ButtonSwitcher;
		btnManager->SetWidth();
		AddObject(btnManager, Layer::UI);

		vector<Button*> buttons;
		for (int i = 0; i < 2; i++)
		{
			Button* obj = new Button;
			obj->SetPos({ (WINDOW_WIDTH / 2.f) - 100.f + 200.f * i, WINDOW_HEIGHT / 2 + 100.f });
			obj->SetSize({ 150,40 });
			AddObject(obj, Layer::DEFAULT);

			switch (i)
			{
			case 1:
			{
				obj->SetButtonType(UIType::SKIP);
				obj->SetOnClick([this]() {
					GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
					}, "취소");
			}
			break;
			case 0:
			{
				obj->SetButtonType(UIType::EXCHANGE);
				obj->SetOnClick([this]() {
					bool isPlayer1 = AskTargetUnit();
					UnitType type = isPlayer1 ? UnitType::PLAYER1 : UnitType::PLAYER2;
					GET_SINGLE(CombatManager)->SetUnitData(type);
					GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
					}, "시작");
			}
			break;
			}

			buttons.push_back(obj);
		}
		btnManager->SetButtons(buttons);
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
		SetTextColor(_hdc, RGB(50, 50, 50));

		RECT textRect;
		textRect.left = 0;
		textRect.right = WINDOW_WIDTH;
		textRect.top = 0;
		textRect.bottom = 100;

		DrawTextW(_hdc, m_resultText.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
	}

	if (m_isWin == false) {
		GDISelector fontSelector(_hdc, FontType::PIXEL_MIDIUM);

		wstring text = L"ENTER를 눌러 타이틀 가기";

		SetTextColor(_hdc, RGB(50, 50, 50));

		RECT textRect;
		textRect.left = 0;
		textRect.right = WINDOW_WIDTH;
		textRect.top = WINDOW_HEIGHT / 2 + 50.f;
		textRect.bottom = WINDOW_HEIGHT / 2 + 150.f;

		DrawTextW(_hdc, text.c_str(), -1, &textRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
	}

}
void BattleEndScene::Update()
{
	Scene::Update();
	if (m_isWin == false)
	{
		if (GET_KEYUP(KEY_TYPE::ENTER))
			GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
	}
}

bool BattleEndScene::AskTargetUnit()
{
	HWND hwndOwner = GetActiveWindow();
	int ret = ::MessageBoxW(
		hwndOwner,
		L"교환할 유닛을 선택해주세요 :\n\nYes : Player1\nNo : Player2",
		L"유닛 선택",
		MB_YESNO | MB_ICONQUESTION
	);

	switch (ret)
	{
	case IDYES:    return true;
	case IDNO:     return false;
	default:       return true;
	}
}
