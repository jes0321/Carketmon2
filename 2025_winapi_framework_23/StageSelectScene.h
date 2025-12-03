#pragma once
#include "Scene.h"
#include "Stage.h"

class Stage;
class StageSelectScene : public Scene
{
public:
	// Scene을(를) 통해 상속됨
	void Init() override;
	void Update() override;
private:
	void StageDebugLog();
	void MoveStage()
	{
		for (int i = 0; i < m_maxStageIndex + 1; i++)
			for (auto stage : m_stages[i])
				stage->SetPos({ (int)stage->GetPos().x, (-120 * i) + 300 + (m_currentStageLength * 120) });
	}
	void SetCurrentStage(Stage* _stages)
	{
		if (m_currentStage != nullptr)
		{
			m_currentStage->IsSeleted = false;
		}

		m_currentStage = _stages;
		m_currentStage->IsSeleted = true;
	}
	bool ChangeStage(int _stageIndex)
	{
		if (_stageIndex > m_maxStageIndex)
		{
			m_currentStageLength = m_maxStageIndex;
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
	vector<vector<Stage*>> m_stages;
	vector<Stage*> m_beforeofNextStages;
	Stage* m_currentStage = nullptr;
	int m_maxStageIndex = 0;
	int m_currentStageLength = 0;
	int m_currentSelectStageLength = 0;
	int m_currentStageIndex = 0;
};

