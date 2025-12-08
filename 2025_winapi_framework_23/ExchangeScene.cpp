#include "pch.h"
#include "ExchangeScene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CombatManager.h"

void ExchangeScene::Init()
{
	GET_SINGLE(CombatManager)->CombatManager::HealUnit(UnitType::PLAYER1);
	GET_SINGLE(CombatManager)->CombatManager::HealUnit(UnitType::PLAYER2);
}

void ExchangeScene::Update()
{
	Scene::Update();

	if (GET_KEYUP(KEY_TYPE::ENTER))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"StageSelectScene");
	}
}
