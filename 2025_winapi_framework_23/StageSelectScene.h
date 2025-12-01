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
	};
private:
	vector<vector<Stage*>> _stages;
	Stage* m_currentStage = nullptr;
	int m_maxStageIndex = 0;
	int m_currentStageLength = 0;
	int m_currentStageIndex = 0;
};

