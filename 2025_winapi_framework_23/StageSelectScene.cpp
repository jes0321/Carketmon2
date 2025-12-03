#include "pch.h"
#include "StageSelectScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Stage.h"
#include "Button.h"
#include "ButtonSwitcher.h"

const int MinStageCount = 2, MaxStageCount = 4, StageLength = 10;

void StageSelectScene::Init()
{
	int stageNumber = 1;

	m_maxStageIndex = StageLength - 1;

	int randStageType = rand() % StageType::Max;

	for (int i = 0; i < StageLength; i++)
	{
		int stageCount = rand() % MaxStageCount + MinStageCount;

		// 첫 스테이지와 마지막 스테이지 1개로 고정
		if (i == StageLength - 1 || i == 0)
			stageCount = 2;

		vector<Stage*> stageRow;

		for (int j = 1; j < stageCount; j++)
		{
			int posX = (WINDOW_WIDTH / stageCount + 1) * j;

			Stage* obj = new Stage;
			obj->SetPos({ posX , (-120 * i) + 300 });
			obj->SetSize({ 100,100 });
			obj->SettingStage(stageNumber, j - 1, i);
			AddObject(obj, Layer::DEFAULT);
			stageRow.push_back(obj);

			++stageNumber;

			if (i == 0) break;

			Stage* before = m_stages[i - 1][rand() % m_stages[i - 1].size()];
			obj->SettingBeforeStage(before);
			before->AddNextStage(obj);

		}

		//만약 이전 스테이지에서 다음 스테이지가 
		// 설정되지 못한 스테이지가 존재한다면 연결
		if (i > 0)
		{
			for (Stage* prev : m_stages[i - 1])
			{
				if (prev->GetNextStages().empty())
				{
					Stage* randomNext = stageRow[rand() % stageRow.size()];
					prev->AddNextStage(randomNext);
				}
			}
		}

		m_stages.push_back(stageRow);
	}

	SetCurrentStage(m_stages[0][0]);

	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void StageSelectScene::Update()
{
	Scene::Update();

	//StageDebugLog();

	if (GET_KEYDOWN(KEY_TYPE::ENTER) && m_currentStage->IsAvailable == true)
	{
		m_currentStage->IsCompelet = true;
		m_currentStageLength = m_currentSelectStageLength;
		MoveStage();

		for (int i = 0; i < m_stages.size(); i++)
		{
			if (i == m_currentSelectStageLength + 1) break;

			for (auto stage : m_stages[i])
				stage->IsAvailable = false;

		}
		//GET_SINGLE(SceneManager)->LoadScene(L"BattleScene");
	}

	if (GET_KEYUP(KEY_TYPE::UP) || GET_KEYUP(KEY_TYPE::W))
	{
		if (ChangeStage(++m_currentStageLength) == false) return;

		if (m_currentStage->IsCompelet == true
			&& m_currentSelectStageLength < m_currentStageLength)
		{
			m_currentSelectStageLength = m_currentStageLength;
			m_currentStageIndex = m_currentStage->GetNextStages()[0]->GetStageRowIndex();
			SetCurrentStage(m_stages[m_currentSelectStageLength][m_currentStageIndex]);
		}

		MoveStage();
	}
	else if (GET_KEYUP(KEY_TYPE::DOWN) || GET_KEYUP(KEY_TYPE::S))
	{
		if(ChangeStage(--m_currentStageLength) == false) return;

		MoveStage();
	}
	else if (GET_KEYUP(KEY_TYPE::RIGHT) || GET_KEYUP(KEY_TYPE::D))
	{
		// 현재 스테이지 기준으로 이전 스테이지가 없거나 
		// 현재 스테이지가 비활성화 상태이거나
		// 다음 스테이지가 더 이상 없으면 리턴
		if (m_currentStage->GetBeforeStage() == nullptr
			|| m_currentStage->IsAvailable == false
			|| m_currentStage->GetBeforeStage()->GetNextStages().size() <= m_currentStageIndex + 1)
			return;

		++m_currentStageIndex;

		SetCurrentStage(m_currentStage->GetBeforeStage()->GetNextStages()[m_currentStageIndex]);
	}
	else if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::A))
	{
		if (0 > m_currentStageIndex - 1
			|| m_currentStage->IsAvailable == false
			|| m_currentStage->GetBeforeStage() == nullptr) 
			return;

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
}

//이건 디버그 편하게 하려고
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

