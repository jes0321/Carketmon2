#include "pch.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "InputManager.h"

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	if (GET_KEYUP(KEY_TYPE::ENTER))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"StartScene");
		//GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
	}
}
