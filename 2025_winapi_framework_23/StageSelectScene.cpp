#include "pch.h"
#include "StageSelectScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Stage.h"
#include "Button.h"
#include "ButtonSwitcher.h"

void ButtonTest()
{
	cout << "첫 번째 버튼 클릭";
}

void StageSelectScene::Init()
{
	// Object 배치;

	ButtonSwitcher* buttonSwitcher = new ButtonSwitcher;
	buttonSwitcher->SetPos({ WINDOW_WIDTH / 6, 300 });
	buttonSwitcher->SetSize({ 100,100 });
	AddObject(buttonSwitcher, Layer::DEFAULT);

	vector<Button*> buttons;

	for (int i = 0; i < 5; i++)
	{
		Button* obj = new Button;
		obj->SetPos({ WINDOW_WIDTH / 4, (120 * i) - -100 });
		obj->SetSize({ 10,10 });
		AddObject(obj, Layer::DEFAULT);

		if(i == 0)
			obj->SetOnClick(ButtonTest);

		buttons.push_back(obj);
	}

	buttonSwitcher->SetButtons(buttons);

	for (int i = 0; i < 5; i++)
	{
		Stage* obj = new Stage;
		obj->SetPos({ WINDOW_WIDTH / 2, (120 * i) - 300 });
		obj->SetSize({ 100,100 });
		AddObject(obj, Layer::DEFAULT);
		_stages[4 - i] = obj;
	}

	_stages[m_currentStageIndex]->isSeleted = true;

	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void StageSelectScene::Update()
{
	Scene::Update();
	// 엔터가 눌리면 씬을 변경
	if (GET_KEY(KEY_TYPE::ENTER))
	{
		//cout << "전투씬 이동" << endl;
		//GET_SINGLE(SceneManager)->LoadScene(L"TestScene");
	}

	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W))
	{
		if (ChangeStage(++m_currentStageIndex) == false) return;

		int prevVis = 4 - (m_currentStageIndex - 1);
		int currVis = 4 - m_currentStageIndex;
		_stages[prevVis]->isSeleted = false;
		_stages[currVis]->isSeleted = true;



		for (int i = 0; i < 5; i++)
		{
			_stages[i]->SetPos({WINDOW_WIDTH / 2, (120 * i) - 300 + (m_currentStageIndex * 120) });
			_stages[i]->SetSize({ 100,100 });
		}
	}
	if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S))
	{
		if(ChangeStage(--m_currentStageIndex) == false) return;

		int prevVis = 4 - (m_currentStageIndex + 1);
		int currVis = 4 - m_currentStageIndex;
		_stages[prevVis]->isSeleted = false;
		_stages[currVis]->isSeleted = true;


		for (int i = 0; i < 5; i++)
		{
			_stages[i]->SetPos({ WINDOW_WIDTH / 2, (120 * i) - 300 + (m_currentStageIndex * 120) });
			_stages[i]->SetSize({ 100,100 });
		}
	}
}

