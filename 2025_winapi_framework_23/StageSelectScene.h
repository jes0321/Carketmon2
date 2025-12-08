#pragma once
#include "Scene.h"
#include "Stage.h"
#include "StageManager.h"

class StageSelectScene : public Scene
{
public:
	~StageSelectScene() override {}
public:
	// Scene을(를) 통해 상속됨
	void Init() override;
	void Update() override;
public:
	Stage* GetCurrentStage() const { return m_currentStage; }
private:
	void StageDebugLog();
	void GenerateStage();
private:
	StageType RandomStageType()
	{
		int random = rand() % 100;

		if (random < (int)StageType::TreatmentCenter) return StageType::TreatmentCenter;
		else if (random < (int)StageType::Exchange) return StageType::Exchange;
		else return StageType::Normal;
	}
	void MoveStage()
	{
		for (int i = 0; i < StageLength; i++)
			for (auto stage : m_stages[i])
				stage->SetPos({ (int)stage->GetPos().x, (-120 * i) + 300 + (m_currentStageLength * 120) });
	}
	void SetCurrentStage(Stage* _stages)
	{
		if (m_currentStage != nullptr)
			m_currentStage->IsSeleted = false;

		m_currentStage = _stages;
		m_currentStage->IsSeleted = true;

		GET_SINGLE(StageManager)->SetCurrentStage(m_currentStage);
	}
	bool ChangeStage(int _stageIndex)
	{
		if (_stageIndex > StageLength - 1)
		{
			m_currentStageLength = StageLength - 1;
			return false;
		}
		if (_stageIndex < 0)
		{
			m_currentStageLength = 0;
			return false;
		}

		return true;
	}
private:
	const int StageLength = 10;
	const int MaxStageCount = 4;
	const int MinStageCount = 2;
private:
	vector<vector<Stage*>> m_stages;
	Stage* m_currentStage = nullptr;
	int m_currentStageLength = 0;
	int m_currentSelectStageLength = 0;
	int m_currentStageIndex = 0;
};

