#include "pch.h"
#include "StageSelectScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Stage.h"

void StageSelectScene::Init()
{
	// Object 배치

	for (int i = 0; i < 5; i++)
	{
		Stage* obj = new Stage;
		obj->SetPos({ WINDOW_WIDTH / 2, 100 * (i + 10) });
		obj->SetSize({ 100,100 });
	}

	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void StageSelectScene::Update()
{
	Scene::Update();
	// 엔터가 눌리면 씬을 변경
	if (GET_KEY(KEY_TYPE::ENTER))
		GET_SINGLE(SceneManager)->LoadScene(L"TestScene");

	if (GET_KEY(KEY_TYPE::UP, KEY_TYPE::W))
	{
		if (ChangeStage(++m_currentStageIndex)) return;

		for (int i = 0; i < 5; i++)
		{
			_stages[i]->SetPos({WINDOW_WIDTH / 2, 100 * (i + 10)});
			_stages[i]->SetSize({ 100,100 });
		}
	}
	if (GET_KEY(KEY_TYPE::DOWN, KEY_TYPE::S))
	{
		if(ChangeStage(--m_currentStageIndex)) return;

		for (int i = 0; i < 5; i++)
		{
			_stages[i]->SetPos({ WINDOW_WIDTH / 2, 100 * (i + 10) });
			_stages[i]->SetSize({ 100,100 });
		}
	}
}

