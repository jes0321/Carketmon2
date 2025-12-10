#include "pch.h"
#include "StageSelectScene.h"
#include "Object.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CombatManager.h"
#include "Stage.h"
#include "UnitObject.h"
#include "LifeUI.h"
#include "UnitManager.h"
#include "StageManager.h"

StageSelectScene::~StageSelectScene()
{

}

void StageSelectScene::Init()
{
	srand((unsigned int)time(NULL));

	m_LifeCount = GET_SINGLE(CombatManager)->GetLifeCount();

	if (GET_SINGLE(StageManager)->IsReset()) {
		m_stages = GET_SINGLE(StageManager)->GenerateStageMap();
		SetCurrentStage(m_stages[0][0]);
	}

	LifeUI* lifeUI = new LifeUI;
	lifeUI->Init();
	AddObject(lifeUI, Layer::UI);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

void StageSelectScene::Update()
{
	Scene::Update();

	//StageDebugLog();
	//cout << (int)(m_currentStage->GetUnitData()->GetElementType());

	if (GET_KEYDOWN(KEY_TYPE::SPACE) && m_currentStage->IsAvailable == true)
	{
		StageType stageType = m_currentStage->GetStageType();
		GET_SINGLE(CombatManager)->SetEnemy(m_currentStage->GetUnitData());
		m_currentStage->IsCompelet = true;
		m_currentStageLength = m_currentSelectStageLength;
		MoveStage();

		for (int i = 0; i < m_stages.size(); i++)
		{
			if (i == m_currentSelectStageLength + 1) break;

			for (auto stage : m_stages[i])
				stage->IsAvailable = false;
		}

		if (ChangeStage(++m_currentStageLength) == false) return;

		if (m_currentStage->IsCompelet == true
			&& m_currentSelectStageLength < m_currentStageLength)
		{
			m_currentSelectStageLength = m_currentStageLength;
			m_currentStageIndex = m_currentStage->GetNextStages()[0]->GetStageRowIndex();
			SetCurrentStage(m_stages[m_currentSelectStageLength][m_currentStageIndex]);
		}

		MoveStage();

		GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

		switch (stageType)
		{
		case StageType::TreatmentCenter:
			GET_SINGLE(SceneManager)->LoadScene(L"TreatmentCenterScene");
			return;
		case StageType::Exchange:
			GET_SINGLE(SceneManager)->LoadScene(L"ExchangeScene");
			return;
		case StageType::Normal:
			GET_SINGLE(SceneManager)->LoadScene(L"BattleScene");
			return;
		case StageType::Boss:
			GET_SINGLE(SceneManager)->LoadScene(L"BattleScene");
			return;
		}
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
		if (ChangeStage(--m_currentStageLength) == false) return;

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

	for (auto stageRow : m_stages)
		for (auto stage : stageRow)
			stage->Update();
}

void StageSelectScene::Render(HDC _hdc)
{
	for (auto stageRow : m_stages)
		for (auto stage : stageRow)
			stage->Render(_hdc);

}

void StageSelectScene::Release()
{
	Scene::Release();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
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


