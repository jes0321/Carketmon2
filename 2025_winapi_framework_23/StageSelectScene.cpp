#include "pch.h"
#include "StageSelectScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Stage.h"
#include "Button.h"
#include "ButtonSwitcher.h"

const int minStageCount = 2, maxStageCount = 4, stageLength = 10;

void StageSelectScene::Init()
{
	m_maxStageIndex = stageLength - 1;

	for (int i = 0; i < stageLength; i++)
	{
		int stageCount = rand() % maxStageCount + minStageCount;

		if (i == stageLength - 1 || i == 0)
			stageCount = 2;

		cout << stageCount << endl;

		vector<Stage*> stageRow;

		for (int j = 1; j < stageCount; j++)
		{
			int posX = (WINDOW_WIDTH / stageCount + 1) * j;

			Stage* obj = new Stage;
			obj->SetPos({ posX , (120 * i) - 600 });
			obj->SetSize({ 100,100 });
			AddObject(obj, Layer::DEFAULT);
			stageRow.push_back(obj);

			if (i == 0) break;

			Stage* before = _stages[i - 1][rand() % _stages[i - 1].size()];
			obj->SettingBeforeStage(before);

			for (auto prevStage : _stages[i - 1])
			{
				prevStage->AddNextStage(obj);
			}
		}

		_stages.push_back(stageRow);
	}

	SetCurrentStage(_stages[0][0]);

	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void StageSelectScene::Update()
{
	Scene::Update();
	// 엔터가 눌리면 씬을 변경
	if (GET_KEY(KEY_TYPE::ENTER))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"BattleScene");
	}

	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W))
	{
		if (ChangeStage(++m_currentStageLength) == false) return;

		m_currentStageIndex = 0;

		SetCurrentStage(_stages[(stageLength - 1) - m_currentStageLength][m_currentStageIndex]);

		for (int i = 0; i < stageLength; i++)
		{
			for(auto stage : _stages[i])
			{
				stage->SetPos({ (int)stage->GetPos().x, (120 * i) - 600 + (m_currentStageLength * 120) });
			}
		}
	}
	else if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S))
	{
		if(ChangeStage(--m_currentStageLength) == false) return;

		m_currentStageIndex = 0;

		SetCurrentStage(_stages[(stageLength - 1) - m_currentStageLength][m_currentStageIndex]);

		for (int i = 0; i < stageLength; i++)
		{
			for (auto stage : _stages[i])
			{
				stage->SetPos({ (int)stage->GetPos().x, (120 * i) - 600 + (m_currentStageLength * 120) });
			}
		}
	}
	else if (GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D))
	{
		m_currentStage->GetNextStages();
	}
	else if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::A))
	{

	}
}

