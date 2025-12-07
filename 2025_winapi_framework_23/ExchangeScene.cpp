#include "pch.h"
#include "ExchangeScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CombatManager.h"

void ExchangeScene::Init()
{
}

void ExchangeScene::Update()
{
	Scene::Update();

	if (GET_KEYUP(KEY_TYPE::ENTER))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
	}
}
