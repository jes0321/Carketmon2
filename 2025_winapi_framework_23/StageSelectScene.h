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
	bool ChangeStage(int _stageIndex)
	{
		if (_stageIndex > 4)
		{
			m_currentStageIndex = 4;
			return false;
		}
		if (_stageIndex < 0)
		{
			m_currentStageIndex = 0;
			return false;
		}

		return true;
	};
private:
	Stage* _stages[5];
	int m_currentStageIndex = 0;
};

