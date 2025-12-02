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
	int stageNumber = 1;

	m_maxStageIndex = stageLength - 1;

	for (int i = 0; i < stageLength; i++)
	{
		int stageCount = rand() % maxStageCount + minStageCount;

		if (i == stageLength - 1 || i == 0)
			stageCount = 2;

		vector<Stage*> stageRow;

		for (int j = 1; j < stageCount; j++)
		{
			int posX = (WINDOW_WIDTH / stageCount + 1) * j;

			Stage* obj = new Stage;
			obj->SetPos({ posX , (-120 * i) + 300 });
			obj->SetSize({ 100,100 });
			obj->SettingStage(j - 1, stageNumber);
			AddObject(obj, Layer::DEFAULT);
			stageRow.push_back(obj);

			++stageNumber;

			if (i == 0) break;

			Stage* before = _stages[i - 1][rand() % _stages[i - 1].size()];
			obj->SettingBeforeStage(before);
			before->AddNextStage(obj);

		}

		if (i > 0)
		{
			for (Stage* prev : _stages[i - 1])
			{
				if (prev->GetNextStages().empty())
				{
					Stage* randomNext = stageRow[rand() % stageRow.size()];
					prev->AddNextStage(randomNext);
				}
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

	//StageDebugLog();

	// 엔터가 눌리면 씬을 변경
	if (GET_KEY(KEY_TYPE::ENTER))
	{
		GET_SINGLE(SceneManager)->LoadScene(L"BattleScene");
	}

	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W))
	{
		if (ChangeStage(++m_currentStageLength) == false) return;

		m_currentStageIndex = m_currentStage->GetNextStages()[0]->GetStageIndex();

		SetCurrentStage(_stages[m_currentStageLength][m_currentStageIndex]);

		for (int i = 0; i < stageLength; i++)
		{
			for(auto stage : _stages[i])
			{
				stage->SetPos({ (int)stage->GetPos().x, (-120 * i) + 300 + (m_currentStageLength * 120) });
			}
		}
	}
	else if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S))
	{
		if(ChangeStage(--m_currentStageLength) == false) return;

		m_currentStageIndex = m_currentStage->GetBeforeStage()->GetStageIndex();

		SetCurrentStage(_stages[m_currentStageLength][m_currentStageIndex]);

		for (int i = 0; i < stageLength; i++)
		{
			for (auto stage : _stages[i])
			{
				stage->SetPos({ (int)stage->GetPos().x, (-120 * i) + 300 + (m_currentStageLength * 120) });
			}
		}
	}
	else if (GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D))
	{
		if (m_currentStage->GetBeforeStage() == nullptr) return;
		if (m_currentStage->GetBeforeStage()->GetNextStages().size() <= m_currentStageIndex + 1 ) return;

		++m_currentStageIndex;

		SetCurrentStage(m_currentStage->GetBeforeStage()->GetNextStages()[m_currentStageIndex]);
	}
	else if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::A))
	{
		if (0 > m_currentStageIndex - 1 || m_currentStage->GetBeforeStage() == nullptr) return;

		if (m_currentStage->GetBeforeStage()->GetNextStages().size() <= m_currentStageIndex)
		{
			m_currentStageIndex = m_currentStage->GetBeforeStage()->GetNextStages().size() - 1;
		}
		else
		{
			--m_currentStageIndex;
		}


		SetCurrentStage(m_currentStage->GetBeforeStage()->GetNextStages()[m_currentStageIndex]);
	}

	//cout << "Current Stage Index: " << m_currentStageIndex << "StageCount" << _stages[m_currentStageLength].size() << endl;
}

void StageSelectScene::StageDebugLog()
{

	cout << "Current Stage: " << m_currentStage->GetStageNumber() << endl;

	if (m_currentStage->GetBeforeStage() != nullptr)
		cout << "GetBeforeStage: " << m_currentStage->GetBeforeStage()->GetStageNumber() << endl;
	else
		cout << "GetBeforeStage: NULL" << endl;

	if (!m_currentStage->GetNextStages().empty())
	{
		cout << " | Next Stages: " << endl;
		for (int i = 0; i < m_currentStage->GetNextStages().size(); i++)
		{
			cout << m_currentStage->GetNextStages()[i]->GetStageNumber() << endl;
		}
	}
	else
		cout << " | Next Stages: NULL" << endl;
}

