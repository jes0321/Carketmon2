#pragma once
#include "Scene.h"

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
		if (_stageIndex > 4 || _stageIndex < 0)
			return true;

		return false;
	};
private:
	Stage* _stages[5];
	int m_currentStageIndex = 0;
};

